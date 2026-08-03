#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int left, int right) {
    int pivot_index = left + rand() % (right - left + 1);
    int pivot_value = arr[pivot_index];
    
    swap(&arr[pivot_index], &arr[right]);
    int store_index = left;
    
    for (int i = left; i < right; i++) {
        if (arr[i] < pivot_value) {
            swap(&arr[i], &arr[store_index]);
            store_index++;
        }
    }
    swap(&arr[store_index], &arr[right]);
    return store_index;
}

void quickselect(int arr[], int left, int right, int k) {
    if (left >= right) return;
    
    int pivot_index = partition(arr, left, right);
    
    if (pivot_index == k) {
        return;
    } else if (pivot_index > k) {
        quickselect(arr, left, pivot_index - 1, k);
    } else {
        quickselect(arr, pivot_index + 1, right, k);
    }
}

int main() {
    
    int data[] = {12, 3, 5, 7, 4, 19, 26, 2};
    int n = sizeof(data) / sizeof(data[0]);
    int k = 4;
    
    quickselect(data, 0, n - 1, k - 1);
    
    printf("The first %d smallest elements in any order: ", k);

    for (int i = 0; i < k; i++) {
        printf("%d ", data[i]);
    }
    
    printf("\n");
    
    return 0;
}
