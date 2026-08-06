#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sorting.h"
#include "utils.h"

static void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // pi is the partition returning index of the pivot
        // recursion calls for smaller elements
        // and greater or equal elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
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

        quickSort(a, 0, size - 1);

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
