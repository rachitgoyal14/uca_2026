import java.util.*;

public class Main {

    static class MinStack {
        ArrayList<Integer>stack = new ArrayList<>();

        public void push(int val) {
           stack.add(val);
        }

        public void pop() {
           stack.remove(stack.size() - 1);
        }

        public int top() {
            return stack.get(stack.size() - 1);
        }

        public int getMin() { // O(N)
            int minValue = Integer.MAX_VALUE;
            for (int i :stack) {
                if (i < minValue) minValue = i;
            }
            return minValue;
        }
    }

    public static void main(String[] args) {
        MinStack stack = new MinStack();

       stack.push(-2);
       stack.push(0);
       stack.push(-3);

        System.out.println(stack.getMin());

       stack.pop();

        System.out.println(stack.top());
        System.out.println(stack.getMin());
    }
}
