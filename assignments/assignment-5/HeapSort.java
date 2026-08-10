public class HeapSort {

    static void swap(int[] a, int i, int j) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    // sink (heapify) node i down, within a heap of the given size
    static void sink(int[] a, int size, int i) {
        int L = 2 * i + 1;
        int R = 2 * i + 2;
        int largest = i;

        if (L < size && a[L] > a[largest]) largest = L;
        if (R < size && a[R] > a[largest]) largest = R;

        if (largest != i) {
            swap(a, i, largest);
            sink(a, size, largest);
        }
    }

    // bottom-up heap construction: O(n)
    static void buildMaxHeap(int[] a, int n) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            sink(a, n, i);
        }
    }

    static void heapSort(int[] a) {
        int n = a.length;
        buildMaxHeap(a, n);

        // repeatedly move max (root) to the end, shrink heap, re-sink
        for (int end = n - 1; end > 0; end--) {
            swap(a, 0, end);
            sink(a, end, 0);   // heap size is now `end`
        }
    }

    static void print(int[] a) {
        for (int x : a) System.out.print(x + " ");
        System.out.println();
    }

    public static void main(String[] args) {
        int[] a = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6};

        System.out.print("Before: ");
        print(a);

        heapSort(a);

        System.out.print("After:  ");
        print(a);
    }
}