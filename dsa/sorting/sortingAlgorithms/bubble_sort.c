#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "sorting.h"
#include "utils.h"

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                flag = 1;
            }
        }
        if (!flag) break;
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

        bubbleSort(a, size);

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
