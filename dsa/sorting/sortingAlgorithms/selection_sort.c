#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sorting.h"
#include "utils.h"

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
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

        selectionSort(a, size);

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
