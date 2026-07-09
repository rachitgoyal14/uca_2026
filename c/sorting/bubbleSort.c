#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Standard Bubble Sort function
void bubble_sort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

// Helper function to fill array with random numbers
void generate_random_array(int arr[], int n) {
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % 100000;  // Random numbers between 0 and 99,999
  }
}

int main() {
  srand(time(NULL));

  int sizes[] = {1000, 2000, 5000, 10000};
  int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

  for (int i = 0; i < num_sizes; i++) {
    int n = sizes[i];

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
      printf("Memory allocation failed!\n");
      return 1;
    }

    generate_random_array(arr, n);

    clock_t start = clock();
    bubble_sort(arr, n);
    clock_t end = clock();

    double cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Array Size: %d\tTime Taken: %.6f seconds\n", n, cpu_time);

    free(arr);
  }

  return 0;
}
