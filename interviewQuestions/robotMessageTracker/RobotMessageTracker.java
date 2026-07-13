package interviewQuestions.robotMessageTracker;

import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;


public class RobotMessageTracker {

    private static class MessageNode {
        final long timestamp;
        final String message;
        String status; // "ON_HOLD" or "CANCELLED" 

        MessageNode(long timestamp, String message) {
            this.timestamp = timestamp;
            this.message = message;
            this.status = "ON_HOLD";
        }
    }


    private final Map<String, Long> lastPrintedAt = new HashMap<>();

    public boolean shouldPrintMessageI(long timestamp, String message) {
        Long last = lastPrintedAt.get(message);
        if (last == null || timestamp - last >= 10) {
            lastPrintedAt.put(message, timestamp);
            return true;
        }
        return false;
    }

    private final Map<String, MessageNode> latestNodeOf = new HashMap<>();
    private final Queue<MessageNode> pending = new LinkedList<>();

    public List<String> shouldPrintMessageII(long timestamp, String message) {
        MessageNode incoming = new MessageNode(timestamp, message);
        MessageNode previous = latestNodeOf.get(message);

        // A duplicate inside the window cancels BOTH copies.
        if (previous != null && (incoming.timestamp - previous.timestamp) < 10) {
            previous.status = "CANCELLED";
            incoming.status = "CANCELLED";
        }

        latestNodeOf.put(message, incoming);
        pending.offer(incoming);

        List<String> printed = new ArrayList<>();
        while (!pending.isEmpty() && (timestamp - pending.peek().timestamp) >= 10) {
            MessageNode resolved = pending.poll();
            if (resolved.status.equals("ON_HOLD")) {
                String line = resolved.timestamp + " " + resolved.message;
                System.out.println(line);
                printed.add(line);
            }
        }
        return printed;
    }

    private final Map<String, MessageNode> liveEntry = new HashMap<>();
    private final Queue<MessageNode> liveOrder = new LinkedList<>();

    public boolean shouldPrintMessageIII(long timestamp, String message) {
        // Evict anything whose window has fully closed.
        while (!liveOrder.isEmpty() && (timestamp - liveOrder.peek().timestamp) >= 10) {
            MessageNode stale = liveOrder.poll();
            // Only delete from the map if it's still the same node --
            // otherwise a more recent entry for this message would be
            // wiped out by mistake.
            if (liveEntry.get(stale.message) == stale) {
                liveEntry.remove(stale.message);
            }
        }

        MessageNode existing = liveEntry.get(message);
        if (existing != null && (timestamp - existing.timestamp) < 10) {
            return false;
        }

        MessageNode fresh = new MessageNode(timestamp, message);
        liveEntry.put(message, fresh);
        liveOrder.offer(fresh);
        return true;
    }

    /** Exposed only so the demo below can show the space savings. */
    public int liveMapSizeForPartIII() {
        return liveEntry.size();
    }

    public int mapSizeForPartI() {
        return lastPrintedAt.size();
    }

    private static void printOutcome(long timestamp, String message, boolean shouldPrint) {
        if (shouldPrint) {
            System.out.println(timestamp + " " + message);
        } else {
            System.out.println(timestamp + " " + message + " (suppressed)");
        }
    }

    public static void main(String[] args) {
        System.out.println("=== Part I: basic de-duplication ===");
        RobotMessageTracker t1 = new RobotMessageTracker();
        printOutcome(1, "foo", t1.shouldPrintMessageI(1, "foo"));  // expect true
        printOutcome(2, "bar", t1.shouldPrintMessageI(2, "bar"));  // expect true
        printOutcome(3, "foo", t1.shouldPrintMessageI(3, "foo"));  // expect false
        printOutcome(11, "foo", t1.shouldPrintMessageI(11, "foo")); // expect true

        System.out.println();
        System.out.println();
        RobotMessageTracker t2 = new RobotMessageTracker();
        // Expected printed output over the whole sequence: only "2 bar"
        t2.shouldPrintMessageII(1, "foo");   // held
        t2.shouldPrintMessageII(2, "bar");   // held
        t2.shouldPrintMessageII(3, "foo");   // held, cancels ts=1 "foo" too
        t2.shouldPrintMessageII(13, "foo");  // flushes: ts=1(cancelled, skip),
                                              // ts=2 "bar" (ON_HOLD -> PRINT),
                                              // ts=3(cancelled, skip)

        System.out.println();
        System.out.println();
        RobotMessageTracker t3 = new RobotMessageTracker();
        System.out.println(t3.shouldPrintMessageIII(1, "foo"));  // true
        System.out.println(t3.shouldPrintMessageIII(2, "bar"));  // true
        System.out.println(t3.shouldPrintMessageIII(3, "foo"));  // false
        System.out.println(t3.shouldPrintMessageIII(11, "foo")); // true (foo's old entry evicted)
        System.out.println("live map size (III) = " + t3.liveMapSizeForPartIII()); // 2 (bar@2, foo@11)

        // Show unbounded growth of Part I vs bounded growth of Part III
        RobotMessageTracker growth = new RobotMessageTracker();
        for (int i = 0; i < 100000; i++) {
            String msg = "msg-" + i; // every message unique -> worst case
            growth.shouldPrintMessageI(i, msg);
            growth.shouldPrintMessageIII(i, msg);
        }
        System.out.println("After 100000 unique messages, one at a time:");
        System.out.println("  Part I map size   (unbounded) = " + growth.mapSizeForPartI());
        System.out.println("  Part III map size (bounded)   = " + growth.liveMapSizeForPartIII());
    }
}