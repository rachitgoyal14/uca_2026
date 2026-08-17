#include <stdio.h>
int size = 0;
void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
void sink(int heap[], int i) {
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    int max = i;
    if (L < size && heap[L] > heap[max])
        max = L;
    if (R < size && heap[R] > heap[max])
        max = R;
    if (max != i) {
        swap(heap, i, max);
        sink(heap, max);
    }
}
void heapify(int a[], int n) {
    size = n;
    for (int i = n / 2; i >= 0; i--)
        sink(a, i);
}
void heap_sort(int a[], int n) {
    heapify(a, n);
    for (int i = n - 1; i > 0; i--) {
        swap(a, 0, i);
        size--;
        sink(a, 0);
    }
}
void print(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
int main() {
    int a[] = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6};
    int n = sizeof(a) / sizeof(a[0]);

    printf("Before: ");
    print(a, n);

    heap_sort(a, n);

    printf("After:  ");
    print(a, n);

    return 0;
}
