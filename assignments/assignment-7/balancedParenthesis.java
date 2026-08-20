import java.util.ArrayDeque;
import java.util.Deque;

class balancedParenthesis {
    public boolean isValid(String s) {
        Deque<Character> stack = new ArrayDeque<>();

        for (char c : s.toCharArray()) {
            if (c == '(' || c == '{' || c == '[') {
                stack.push(c);
            } else {
                if (stack.isEmpty()) {
                    return false;
                }

                char top = stack.pop();

                if ((c == ')' && top != '(') ||
                    (c == '}' && top != '{') ||
                    (c == ']' && top != '[')) {
                    return false;
                }
            }
        }

        return stack.isEmpty();
    }

    public static void main(String[] args) {
    balancedParenthesis obj = new balancedParenthesis();

    String s1 = "{[()]}";
    System.out.println(s1 + " -> " + obj.isValid(s1));

    String s2 = "{[(])}";
    System.out.println(s2 + " -> " + obj.isValid(s2));
}
}