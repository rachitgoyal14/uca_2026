package dsa.sorting.mergeKSortedLists;

import java.util.*;

public class Main {
    
    // TIME COMPLEXITY: O(N log N) — N = total nodes; heap holds up to N elements, not k
    // SPACE COMPLEXITY: O(N) — heap size O(N), plus N new nodes allocated
   
    public static ListNode mergeKLists(ListNode[] lists) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();

        for (ListNode head : lists) {
            ListNode currentNode = head;

            while (currentNode != null) {
                minHeap.add(currentNode.val);
                currentNode = currentNode.next;
            }
        }
        
        // create a dummy node to whose next can be returned at the end of the function
        ListNode dummyNode = new ListNode(-1);
        ListNode pointerNode = dummyNode;

        while (!minHeap.isEmpty()) {
            ListNode newNode = new ListNode(minHeap.poll());
            pointerNode.next = newNode;
            pointerNode = newNode;
        }

        return dummyNode.next;
    }
    
    
    // TIME COMPLEXITY: O(N log k) — heap holds at most k elements (one per active list)
    // SPACE COMPLEXITY: O(k) — heap size bounded by k, nodes are relinked not recreated
    
    public static ListNode mergeKListOptimized(ListNode[] lists) {
        if (lists.length == 0) 
            return null;

        PriorityQueue<ListNode> minHeap = new PriorityQueue<>((a, b) -> Integer.compare(a.val, b.val));

        for (ListNode head : lists) {
            if (head != null)
                minHeap.add(head);
        }

        ListNode dummyNode = new ListNode(-1);
        ListNode pointerNode = dummyNode;

        while (minHeap.size() != 0) {
            ListNode currentNode = minHeap.poll();
            pointerNode.next = currentNode;
            pointerNode = currentNode;

            // keep on adding the next nodes of the heads since the input lists are already sorted
            if (currentNode.next != null) 
                minHeap.add(currentNode.next);
        }

        return dummyNode.next;

    }

    public static void main(String[] args) {

        ListNode[] lists = {
                new ListNode(1, new ListNode(4, new ListNode(5))),
                new ListNode(1, new ListNode(3, new ListNode(4))),
                new ListNode(2, new ListNode(6))
        };

        ListNode result = mergeKListOptimized(lists);

        while (result != null) {
            System.out.print(result.val + " ");
            result = result.next;
        }
        System.out.println();
    }
}