package questions.consecutiveIntegers;

import java.util.*;

public class solution {

    public static int lengthOfLongestConsecutiveIntegers(int[] arr) {

        int maximumLength = 0;
        HashSet<Integer> uniqueIntegers = new HashSet<>();
        
        for (int i: arr) {
            uniqueIntegers.add(i);
        }

        for (int val: uniqueIntegers) {
            int len = 1; // we already get a minimum length of 1

            if (uniqueIntegers.contains(val - 1)) continue; // look for a smaller number, beginning of a number
            else {
                int possibleBeginning = val;
                while (uniqueIntegers.contains(possibleBeginning + 1)) {
                    len += 1;
                    possibleBeginning += 1;
                }
            }

            maximumLength = Math.max(maximumLength, len);
        }

        return maximumLength;

    }


    public static void main(String[] args) {
        
        int[] inputArr1 = {100, 4, 200, 1, 2};
        int[] inputArr2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
        int[] inputArr3 = {-2, -3, 3, 0, 0, 2};
        int[] inputArr4 = {-100, 14, 200, 1, 2, 3, 4, 5, 6, 7, 8};
        int[] inputArr5 = {1, 1, 200, 1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13};

        int maxLen = lengthOfLongestConsecutiveIntegers(inputArr5);
        System.out.println(maxLen);

    }

}
