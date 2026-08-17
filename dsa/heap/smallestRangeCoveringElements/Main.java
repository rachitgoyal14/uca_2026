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
        
        // Test case 1: Basic case
        List<List<Integer>> nums1 = new ArrayList<>();
        nums1.add(Arrays.asList(4, 10, 15, 24, 26));
        nums1.add(Arrays.asList(0, 9, 12, 20));
        nums1.add(Arrays.asList(5, 18, 22, 30));
        int[] result1 = solution.smallestRange(nums1);
        System.out.println("Test 1: " + Arrays.toString(result1));
        
        // Test case 2: Two lists
        List<List<Integer>> nums2 = new ArrayList<>();
        nums2.add(Arrays.asList(1, 2, 3));
        nums2.add(Arrays.asList(1, 2, 3));
        int[] result2 = solution.smallestRange(nums2);
        System.out.println("Test 2: " + Arrays.toString(result2));
        
        // Test case 3: Single element in each list
        List<List<Integer>> nums3 = new ArrayList<>();
        nums3.add(Arrays.asList(5));
        nums3.add(Arrays.asList(10));
        nums3.add(Arrays.asList(15));
        int[] result3 = solution.smallestRange(nums3);
        System.out.println("Test 3: " + Arrays.toString(result3));
        
        // Test case 4: Overlapping ranges
        List<List<Integer>> nums4 = new ArrayList<>();
        nums4.add(Arrays.asList(1, 2, 3, 4, 5));
        nums4.add(Arrays.asList(1, 2, 3, 4, 5));
        int[] result4 = solution.smallestRange(nums4);
        System.out.println("Test 4: " + Arrays.toString(result4));
        
        // Test case 5: Larger gap between lists
        List<List<Integer>> nums5 = new ArrayList<>();
        nums5.add(Arrays.asList(1, 100));
        nums5.add(Arrays.asList(11, 200));
        nums5.add(Arrays.asList(21, 300));
        int[] result5 = solution.smallestRange(nums5);
        System.out.println("Test 5: " + Arrays.toString(result5));
        
        // Test case 6: Three lists with common range
        List<List<Integer>> nums6 = new ArrayList<>();
        nums6.add(Arrays.asList(4, 10, 15, 24, 26));
        nums6.add(Arrays.asList(0, 9, 12, 20));
        nums6.add(Arrays.asList(5, 18, 22, 30));
        int[] result6 = solution.smallestRange(nums6);
        System.out.println("Test 6: " + Arrays.toString(result6));
    }
    
}
