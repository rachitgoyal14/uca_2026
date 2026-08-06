package dsa.stacks.implementStack;
import java.util.*;

public class mySolution {

    static class MinStack {
        ArrayList<Integer>stack = new ArrayList<>();
        ArrayList<Integer> minStack = new ArrayList<>(); // maintain a minStack to store the minimum values as found

        public void push(int val) {
            stack.add(val); // push the value into the normal wala stack
            if ((minStack.size() == 0) || (val <= minStack.get(minStack.size() - 1))) {
                // normal stack is empty OR value to be added is the MINIMUM
                minStack.add(val); // push the value into the minStack if 
            }
        }

        public void pop() {
            validate();

            int toBeRemoved = stack.get(stack.size() - 1);
            stack.remove(stack.size() - 1);

            if (minStack.get(minStack.size() - 1).intValue() == toBeRemoved) {
                minStack.remove(minStack.size() - 1);
            }
        }

        public int top() {
            validate();
            return stack.get(stack.size() - 1);
        }

        public int getMin() { 
            validate();
            return minStack.get(minStack.size() - 1);
        }

        private void validate() {
            if (stack.size() == 0) {
                throw new NoSuchElementException("Stack is empty!");
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
