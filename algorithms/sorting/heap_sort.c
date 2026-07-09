#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sorting.h"
#include "utils.h"

static void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main(void) {
    struct timeval te;
    int size = 8000;
    int step = 4000;

    for (int i = 0; i < 8; i++) {
        int* a = (int*)malloc(size * sizeof(int));
        generateAsc(a, size);
        // printArr(a, size);

        gettimeofday(&te, NULL);
        long long start = te.tv_sec * 1000LL + te.tv_usec / 1000;

        heapSort(a, size);

        gettimeofday(&te, NULL);
        long long end = te.tv_sec * 1000LL + te.tv_usec / 1000;

        printf("%lld\n", end - start);
        // printArr(a, size);

        free(a);
        size += step;
    }
    printf("\n");
    return 0;
}
