public class intersectionOf2SortedLLs {

    public static Node findIntersection(Node head1, Node head2) {

        // if either of the heads is null, return a null value itself
        if (head1 == null || head2 == null) {
            return null;
        }
        
        Node resultHead = null; // the node to be returned
        Node resultTail = null; // the node that tracks the end of the newly created linked list

        while (head1 != null && head2 != null) {
            if (head1.data == head2.data) {
                Node newNode = new Node(head1.data);

                if (resultHead == null) {
                    // assign this to the resultHead if this is the first common element found
                    resultHead = newNode;
                    resultTail = newNode;
                } else {
                    // not the first element ? => connect this node to the linkedlist and assign tail
                    resultTail.next = newNode;
                    resultTail = newNode;
                }

                // move both the pointers forward
                head1 = head1.next;
                head2 = head2.next;

            } else if (head1.data < head2.data) {
                head1 = head1.next;
            } else {
                head2 = head2.next;
            }
        }

        return resultHead;
       
    }

    public static void printList(Node head) {
        Node current = head;

        while (current != null) {
            System.out.print(current.data + " -> ");
            current = current.next;
        }

        System.out.println("null\n");
    }

    public static void main(String[] args) {

        LinkedList list1 = new LinkedList();
        list1.add(1);
        list1.add(2);
        list1.add(2);
        list1.add(3);
        list1.add(4);

        LinkedList list2 = new LinkedList();
        list2.add(2);
        list2.add(2);
        list2.add(2);
        list2.add(4);

        System.out.println("First Linked List:");
        printList(list1.head);

        System.out.println("Second Linked List:");
        printList(list2.head);

        Node intersection = findIntersection(list1.head, list2.head);

        System.out.println("Intersection:");
        printList(intersection);
    }
}
