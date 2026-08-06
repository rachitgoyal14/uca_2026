package dsa.hashing.robotMessageTracker;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

class RobotMessageTracker {

    
    private final Map<String, Long> lastPrintedAt;

    public RobotMessageTracker() {
        lastPrintedAt = new HashMap<>();
    }

    /**
     * Part I: return true if this message should be printed at timestamp.
     * Behavior: allow message if it was never printed in the last 10 seconds.
     */
    public boolean shouldPrintMessageI(long timestamp, String message) {
        Long prev = lastPrintedAt.get(message);
        if (prev == null || timestamp - prev >= 10) {
            lastPrintedAt.put(message, timestamp);
            return true;
        }
        return false;
    }

    // ------------------ Part II ------------------
    private static class MessageNode {
        final long timestamp;
        final String message;
        boolean cancelled;

        MessageNode(long t, String m) {
            timestamp = t;
            message = m;
            cancelled = false;
        }
    }

    private final Map<String, MessageNode> latestNodeOf = new HashMap<>();
    private final Queue<MessageNode> pending = new LinkedList<>();

    /**
     * Part II: delayed decision.
     */
    public void shouldPrintMessageII(long timestamp, String message) {
        MessageNode node = new MessageNode(timestamp, message);

        MessageNode prev = latestNodeOf.get(message);
        if (prev != null && timestamp - prev.timestamp < 10) {
            prev.cancelled = true;
            node.cancelled = true;
        }

        latestNodeOf.put(message, node);
        pending.add(node);

        while (!pending.isEmpty() && timestamp - pending.peek().timestamp >= 10) {
            MessageNode head = pending.poll();
            if (!head.cancelled) {
                System.out.println(head.timestamp + " " + head.message);
            }
        }
    }

    // ------------------ Part III ------------------
    private final Map<String, MessageNode> liveEntry = new HashMap<>();
    private final Queue<MessageNode> liveOrder = new LinkedList<>();

    /**
     * Part III: bounded-memory version.
     */
    public boolean shouldPrintMessageIII(long timestamp, String message) {

        while (!liveOrder.isEmpty() && timestamp - liveOrder.peek().timestamp >= 10) {
            MessageNode head = liveOrder.poll();
            MessageNode current = liveEntry.get(head.message);

            if (current == head) {
                liveEntry.remove(head.message);
            }
        }

        if (!liveEntry.containsKey(message)) {
            MessageNode node = new MessageNode(timestamp, message);
            liveEntry.put(message, node);
            liveOrder.add(node);
            return true;
        }

        return false;
    }

    // ------------------ Demo / main ------------------
    public static void main(String[] args) {
        System.out.println("--- Part I demo ---");
        RobotMessageTracker r1 = new RobotMessageTracker();
        System.out.println(r1.shouldPrintMessageI(1, "foo"));
        System.out.println(r1.shouldPrintMessageI(2, "bar"));
        System.out.println(r1.shouldPrintMessageI(3, "foo"));
        System.out.println(r1.shouldPrintMessageI(11, "foo"));

        System.out.println("\n--- Part II demo ---");
        RobotMessageTracker r2 = new RobotMessageTracker();
        r2.shouldPrintMessageII(1, "foo");
        r2.shouldPrintMessageII(2, "bar");
        r2.shouldPrintMessageII(3, "foo");
        r2.shouldPrintMessageII(13, "foo");

        System.out.println("\n--- Part III demo ---");
        RobotMessageTracker r3 = new RobotMessageTracker();
        System.out.println(r3.shouldPrintMessageIII(1, "foo"));
        System.out.println(r3.shouldPrintMessageIII(2, "bar"));
        System.out.println(r3.shouldPrintMessageIII(3, "foo"));
        System.out.println(r3.shouldPrintMessageIII(12, "foo"));
    }
}