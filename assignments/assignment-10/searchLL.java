public class searchLL {

    public static String search(Node head1, Node head2) {
        boolean found = false;

        // handle the edge cases wisely
        if (head1 == null) {
            return "Yes";
        }

        if (head2 == null) {
            return "No";
        }

        while (head2 != null) {

            if (head1.data == head2.data) {

                Node current1 = head1;
                Node current2 = head2;

                // start checking
                while (current1 != null && current2 != null
                        && current1.data == current2.data) {

                    current1 = current1.next;
                    current2 = current2.next;
                }

                // entire head1 was matched
                if (current1 == null) {
                    found = true;
                    break;
                }
            }

            head2 = head2.next;
        }

        String response = found ? "Yes" : "No";
        return response;
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
        list1.add(3);
        list1.add(4);
        list1.add(5);

        System.out.println("first linked list:");
        printList(list1.head);

        LinkedList list2 = new LinkedList();

        list2.add(4);
        list2.add(5);

        System.out.println("second linked list:");
        printList(list2.head);

        String response = search(list2.head, list1.head);

        System.out.println(response);
    }
}