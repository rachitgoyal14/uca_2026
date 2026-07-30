import java.util.NoSuchElementException;
import java.util.*;

public class betterSolution {
    static class MinStack {
    
        class Node {
            int data;
            Node next;
            int currMin;
            Node(int data) {
                this.data = data;
                this.currMin = data;
            }
        }

        Node head;

        public MinStack() {
            head = null;
        }

        
        public void push(int val) {
            Node newNode = new Node(val);
            
            if (head != null) {
                newNode.next = head;
                newNode.currMin= Math.min(newNode.currMin, head.currMin);
            }

            head = newNode;
        }
        
        public void pop() {
            validate();
            head = head.next;
        }

        public int top() {
            validate();
            return head.data;
        }

        public int getMin() {
            validate();
            return head.currMin;
        }

        private void validate() {
            if (head == null) {
                throw new NoSuchElementException("No element is present");
            }
        } 
    }

     public static void main(String[] args) {
        MinStack stack = new MinStack();
        // System.out.println(stack.getMin());
        stack.push(-2);
        stack.push(0);
        stack.push(-3);


        System.out.println(stack.getMin());

        stack.pop();

        System.out.println(stack.top());
        System.out.println(stack.getMin());
    }
}

// // there are operations that you can do on the data
// // there are operations that you can do on the definition of the data
