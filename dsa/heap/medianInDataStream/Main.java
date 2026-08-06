package dsa.heap.medianInDataStream;

import java.util.*;

public class Main {

    PriorityQueue<Integer> large = new PriorityQueue<>();
    PriorityQueue<Integer> small = new PriorityQueue<>(Collections.reverseOrder());
    
    public void MedianFinder() {

    }
    
    public void addNum(int num) {
        // add to the smaller half
        small.offer(num);

        // ensure  all elements in small <= all in large
        large.offer(small.poll());

        // now balance sizes
        if (large.size() > small.size() + 1) small.offer(large.poll());
    }
    
    public double findMedian() {
        // odd numebr of elements
        if (large.size() > small.size()) 
            return large.peek();
        // even number of elements
        return ((double) small.peek() + large.peek()) / 2.0;
    }
}

