#include <stdio.h>

int size = 0;

void swap(int a[], int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int sizeOf() {
    return size;
}

void swim(int heap[], int i) {
    if (i == 0) return;
    int p = (i - 1) / 2;
    if (heap[p] < heap[i]) {
        swap(heap, p, i);
        swim(heap, p);
    }
}

void insert(int heap[], int key) {
    printf("inserting %d\n", key);
    heap[size] = key;
    swim(heap, size);
    size++;
}

int get_max(int heap[]) {
    return heap[0];
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

int del_max(int heap[]) {
    if (sizeOf() == 0) {
        printf("Underflow\n");
        return -1;
    }
    int res = get_max(heap);
    swap(heap, 0, size - 1);
    size--;
    sink(heap, 0);
    return res;
}


void print(int a[]) {
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");
}


int main() {
    int heap[20];
    insert(heap, 5);
    insert(heap, 4);
    insert(heap, 8);
    insert(heap, 9);
    insert(heap, 1);
    insert(heap, 2);

    print(heap);
    
    printf("Max = %d\n", get_max(heap));
    
    del_max(heap);
    
    print(heap);
    printf("Max = %d\n", get_max(heap));
    
    return 0;
}
