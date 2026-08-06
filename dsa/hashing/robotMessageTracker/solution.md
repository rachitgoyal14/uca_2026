# Robot Message Tracker - Approach

Implementation: `robotMessageTracker.java` (methods `shouldPrintMessageI`,
`shouldPrintMessageII`, `shouldPrintMessageIII`).

Assumption used throughout (standard for this problem): calls arrive with
**non-decreasing timestamps** - the server never receives an event "from
the past" relative to the previous call.

---

## Part I - basic de-duplication

**Approach.** Keep one `HashMap<String, Long>` mapping each message to the
timestamp it was *last printed at*. On each call:

- If the message has never been seen, or `timestamp - lastPrinted >= 10`,
  print it and update the map with the new timestamp.
- Otherwise return `false` and **leave the map untouched** - the suppressed
  call at `t=3` must not overwrite `foo`'s stored timestamp of `1`, or the
  call at `t=11` would incorrectly still look too soon (`11 - 3 = 8 < 10`
  instead of the correct `11 - 1 = 10 >= 10`).

**Complexity.** `O(1)` time per call. `O(U)` space, where `U` is the number
of *distinct* messages seen over the program's entire lifetime - the map
never shrinks. That growth is what Part III fixes.

---

## Part II - mutual suppression within a window

**Why this needs a different design.** In Part I, a message could be
approved the instant it arrived, because the decision only depended on the
*past*. Here, an incoming message can retroactively invalidate one that was
already accepted (e.g. `t=1 "foo"` looks fine until `t=3 "foo"` shows up and
cancels it too). That means no message can be safely printed the moment it
arrives - we have to wait until its 10-second window closes with no
duplicate appearing, before committing to "print" or "cancel."

**Approach - delayed decision via a FIFO queue.**

1. Keep a `HashMap<String, MessageNode> latestNodeOf`, mapping each message
   to the node created for its *most recent* occurrence.
2. Keep a FIFO `Queue<MessageNode> pending` in arrival order.
3. On each call:
   - Create a node for the incoming `(timestamp, message)`, status
     `ON_HOLD`.
   - If a previous node exists for this message and
     `newTimestamp - prevTimestamp < 10`, mark **both** the previous node
     and the new node `CANCELLED`. (Mutating the previous node in place is
     what lets a decision made *now* retroactively affect an entry already
     sitting in the queue - no need to search the queue for it.)
   - Update `latestNodeOf[message]` to the new node, and enqueue it.
   - Flush the front of the queue: while the head node's window has fully
     elapsed (`timestamp - head.timestamp >= 10`), pop it. If it's still
     `ON_HOLD`, print it; if `CANCELLED`, discard it.

**Trace of the example:**

| call | queue after processing | printed this call |
|---|---|---|
| `(1, foo)` | `[1:foo·ON_HOLD]` | *(nothing yet - window not closed)* |
| `(2, bar)` | `[1:foo·ON_HOLD, 2:bar·ON_HOLD]` | *(nothing yet)* |
| `(3, foo)` | `[1:foo·CANCELLED, 2:bar·ON_HOLD, 3:foo·CANCELLED]` | *(nothing yet - t=1's window still open)* |
| `(13, foo)` | flush pops `1:foo`(cancelled, skip), `2:bar`(ON_HOLD → **print "2 bar"**), `3:foo`(cancelled, skip); `13:foo·ON_HOLD` stays queued | **`2 bar`** |

Only `"2 bar"` is ever printed. `13:foo` is still sitting in the queue at
the end, waiting for its own window (`t=23`) to close before it can be
confirmed and printed.

**Complexity.** Amortized `O(1)` time per call (each node is pushed once
and popped once). Space is `O(W)`, where `W` is the number of messages that
arrived within the last open 10-second window - bounded by traffic rate,
not by total history.

---

## Part III - bounding the hashmap's memory

This is a well-known follow-up once a candidate produces the Part I
solution: the interviewer points out that `HashMap<String, Long>` never
evicts anything, so a service running for months holds every distinct
message string it has ever seen, even though only the last 10 seconds'
worth is ever actually useful.

**Approach - hashmap + FIFO queue, with lazy eviction.**

Reuse the `MessageNode` idea from Part II, but now the goal is to keep the
*live map itself* small, not to delay decisions:

1. `HashMap<String, MessageNode> liveEntry` - same role as Part I's map,
   but stores node references instead of raw timestamps.
2. `Queue<MessageNode> liveOrder` - every node inserted into `liveEntry` is
   also appended here, in arrival order.
3. On each call, **before** doing anything else, evict from the *front* of
   `liveOrder` while the head node's window has closed
   (`timestamp - head.timestamp >= 10`). For each evicted node, remove it
   from `liveEntry` **only if `liveEntry.get(node.message) == node`** -
   i.e. only if that message hasn't since been refreshed by a newer node
   further back in the queue. This guard prevents a live, more recent
   entry from being wiped out by mistake.
4. Then answer exactly like Part I: if `message` isn't in `liveEntry`, or
   its stored timestamp is `>= 10` seconds old, insert/refresh it (into
   both the map and the queue) and return `true`; otherwise return `false`.

Because a node is only appended when a message is actually printed, and
it's removed the first time its window closes, both `liveEntry` and
`liveOrder` only ever hold entries for messages that printed within the
**trailing** 10-second window - not the entire history.

This matches the standard write-ups of this follow-up: they flag the
unbounded-map drawback and describe pairing the map with a queue (or a
doubly linked list, if you want to splice out a specific stale run in one
step rather than evicting one node at a time) to release stale entries.
The FIFO-queue-with-lazy-eviction version here is the simpler of the two
and has the same amortized cost.

**Demonstration (100,000 all-distinct messages, one call each, in
`RobotMessageTracker.main`):**

| structure | size after all calls |
|---|---|
| Part I map (`lastPrintedAt`) | 100,000 |
| Part III map (`liveEntry`) | 10 |

(10 is exactly right here - with one call per second and a 10-second
window, at most 10 messages are ever "alive" at once.)

**Complexity.** Amortized `O(1)` time per call - every node is pushed to
the queue exactly once and popped exactly once over the program's
lifetime, so total eviction work across `n` calls is `O(n)`. Space is
`O(K)`, where `K` is the number of *distinct* messages seen within the
trailing 10-second window - not the number of distinct messages seen ever.