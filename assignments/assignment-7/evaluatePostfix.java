import java.util.*;

public class evaluatePostfix {

    static void calculate(Stack<Integer> val, char operator) {

        int v2 = val.pop();
        int v1 = val.pop();

        if (operator == '+') val.push(v1 + v2);
        else if (operator == '-') val.push(v1 - v2);
        else if (operator == '*') val.push(v1 * v2);
        else if (operator == '/') val.push(v1 / v2);
    }

    public static int evaluatePostfixExpression(String str) {
        Stack<Integer> val = new Stack<>();

        for (int i = 0; i < str.length(); i++) {
            char ch = str.charAt(i);
            if (Character.isDigit(ch)) val.push(ch - '0');
            else calculate(val, ch);
        }
        return val.peek();
    }

    public static void main(String[] args) {

        String str = "953+4*2/-";

        int result = evaluatePostfixExpression(str);

        System.out.println("Postfix : " + str);
        System.out.println("Result  : " + result);
    }
}