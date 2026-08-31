package dsa.heap.smallestRangeCoveringElements;
import java.util.*;

public class Main {
    
    
    class Info {
        int value;
        int valueIndex;
        int listIndex;

        Info(int value, int valueIndex, int listIndex) {
            this.value = value;
            this.valueIndex = valueIndex;
            this.listIndex = listIndex;
        }
    }

    public int[] smallestRange(List<List<Integer>> nums) {
        int n = nums.size();

        int currentLargestNumber = Integer.MIN_VALUE;
        // use a custom comparator priority queue
        PriorityQueue<Info> minHeap = new PriorityQueue<>((a, b) -> Integer.compare(a.value, b.value));

        int lowerBound = Integer.MAX_VALUE;
        int upperBound = Integer.MIN_VALUE;

        int bestRange  = Integer.MAX_VALUE;

        // add the first Info into the Heap
        // and while adding it, keep a track of the current largest number
        for (int i = 0; i < n; i++) {
            int value = nums.get(i).get(0);

            minHeap.add(new Info(value, 0, i));
            currentLargestNumber = Math.max(currentLargestNumber, value);
        }

        lowerBound = minHeap.peek().value;
        upperBound = currentLargestNumber;
        bestRange = upperBound - lowerBound;

        while (minHeap.isEmpty() != true) {
            Info minElement = minHeap.poll();
            int listIndexOfMinElement = minElement.listIndex;
            int indexOfMinElement = minElement.valueIndex;

            if (indexOfMinElement + 1 < nums.get(listIndexOfMinElement).size()) {
                int valueToInsert = nums.get(listIndexOfMinElement).get(indexOfMinElement + 1);
                minHeap.offer(new Info(valueToInsert, indexOfMinElement + 1, listIndexOfMinElement));

                currentLargestNumber = Math.max(currentLargestNumber, valueToInsert);
            } else {
                break;
            }

            int currentRange = currentLargestNumber - minHeap.peek().value;

            if (currentRange < bestRange) {
                bestRange = currentRange;
                lowerBound = minHeap.peek().value;
                upperBound = currentLargestNumber;
            }
        }

        return new int[]{lowerBound, upperBound};
    }

    public static void main(String[] args) {
        Main solution = new Main();
        
        List<List<Integer>> nums = new ArrayList<>();
        nums.add(Arrays.asList(4, 10, 15, 24, 26));
        nums.add(Arrays.asList(0, 9, 12, 20));
        nums.add(Arrays.asList(5, 18, 22, 30));
        int[] result = solution.smallestRange(nums);
        System.out.println("Test 1: " + Arrays.toString(result));
        
       
    }
    
}
