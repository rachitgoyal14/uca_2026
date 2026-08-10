import java.util.Collections;
import java.util.PriorityQueue;

class MedianFinder {
    PriorityQueue<Integer> large = new PriorityQueue<>();
    PriorityQueue<Integer> small = new PriorityQueue<>(Collections.reverseOrder());

    public MedianFinder() {}

    public void addNum(int num) {
        // add to small first
        small.add(num);

        // then add to large
        // why? => ensure all elements in small are smaller than that in the large
        large.offer(small.poll());

        // if large size increases too much, remove and add to small
        if (large.size() > small.size() + 1) {
            small.add(large.poll());
        }
    }

    public double findMedian() {
        if (large.size() > small.size()) return large.peek();
        return ((double) large.peek() + small.peek()) / 2;
    }
}

public class MedianInDataStream {
    public static void main(String[] args) {
        MedianFinder mf = new MedianFinder();
        int[] stream = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6};

        for (int num : stream) {
            mf.addNum(num);
            System.out.printf("Inserted %d -> Median = %.2f%n", num, mf.findMedian());
        }
    }
}