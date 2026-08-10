#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sorting.h"
#include "utils.h"

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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

        insertionSort(a, size);

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
