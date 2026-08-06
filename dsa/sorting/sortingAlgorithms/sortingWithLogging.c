#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void copyArray(int source[], int dest[], int n) {
    memcpy(dest, source, n * sizeof(int));
}

void generateRan(int arr[],int n){
        for(int i=0;i<n;i++){
                arr[i] = rand();
        }
}

void generateAsc(int arr[], int n){
        for(int i = 0;i < n; i++){
                arr[i] = i + 1;
        }
}

void generateDesc(int arr[], int n){
        for(int i = 0;i < n; i++){
                arr[i] = n - i;
        }
}

void printArr(int arr[], int n){
        for(int i = 0; i < n; i++){
                printf("%d", arr[i]);
        }
}

void bubbleSort(int arr[],int n){
        for(int i = 0; i < n; i++){
                int flag = 0;
                for(int j = 0; j < n-i-1; j++){
                        if(arr[j] > arr[j+1]){
                                int temp = arr[j+1];
                                arr[j+1] = arr[j];
                                arr[j] = temp;
                                flag = 1;
                        }
                }
        if(!flag) break;
        }
}


void insertionSort(int arr[],int n){
        for(int i = 1;i < n; i++){
                int key = arr[i];
                int j = i-1;
                while(j >= 0 && arr[j] > key){
                        arr[j+1] = arr[j];
                        j--;
                }
                arr[j+1] = key;
        }
}

void selectionSort(int arr[],int n){
        for(int i = 0; i<n; i++){
                int min_idx = i;
                for(int j = i+1;j < n; j++){
                        if(arr[j] < arr[min_idx]){
                                min_idx = j;
                        }
                }
                int temp = arr[i];
                arr[i] = arr[min_idx];
                arr[min_idx] = temp;
        }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
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
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r){
    // creating and filling up these tempoarary arrays
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // // merging merging merging
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
   // // j pointer is out of bounds
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  // // i pointer is out of bounds
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void heapify(int arr[], int n, int i){

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

void heapSort(int arr[], int n){

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}
// //  timing wrapper function
double measureTime(void (*sortFunc)(int[], int), int arr[], int n) {
    clock_t start = clock();
    sortFunc(arr, n);
    clock_t end = clock();
    return ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
}

// // creating special wrapper functions for certain sorting algorithms having unique parameters

// special wrapper for quickSort
double measureQuickSortTime(int arr[], int n) {
    clock_t start = clock();
    quickSort(arr, 0, n - 1);
    clock_t end = clock();
    return ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
}

// special wrapper for mergeSort
double measureMergeSortTime(int arr[], int n) {
    clock_t start = clock();
    mergeSort(arr, 0, n - 1);
    clock_t end = clock();
    return ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL)); // seed for random generation

    int sizes[] = {8000, 12000, 16000, 20000, 24000, 28000, 32000, 36000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("--- BENCHMARK RESULTS (Time in Milliseconds) ---\n\n");

    // NEW: results.csv so the numbers can be pivoted/plotted directly, instead of re-typing terminal output
    FILE* csv = fopen("results.csv", "w");
    fprintf(csv, "InputType,Size,Bubble,Insertion,Selection,Quick,Merge,Heap\n");

    const char* inputTypes[] = {"Random", "Ascending", "Descending"};

    for (int t = 0; t < 3; t++) {
        printf("==================================================\n");
        printf(" INPUT TYPE: %s\n", inputTypes[t]);
        printf("==================================================\n");
        printf("Size\tBubble\tInsertion\tSelection\tQuick\tMerge\tHeap\n");

        for (int s = 0; s < numSizes; s++) {
            int n = sizes[s];

            // allocate memory dynamically to prevent stack overflows
            int* baseArr = (int*)malloc(n * sizeof(int));
            int* testArr = (int*)malloc(n * sizeof(int));

            // generate the required array layout
            if (t == 0) generateRan(baseArr, n);
            else if (t == 1) generateAsc(baseArr, n);
            else generateDesc(baseArr, n);

            double t_bubble, t_insert, t_select, t_quick, t_merge, t_heap;

            // 1. Bubble Sort
            copyArray(baseArr, testArr, n);
            t_bubble = measureTime(bubbleSort, testArr, n);

            // 2. Insertion Sort
            copyArray(baseArr, testArr, n);
            t_insert = measureTime(insertionSort, testArr, n);

            // 3. Selection Sort
            copyArray(baseArr, testArr, n);
            t_select = measureTime(selectionSort, testArr, n);

            // 4. Quick Sort
            // Warning: Quick sort with fixed last-element pivot will hit O(n^2) worst case on sorted/reverse arrays.
            // If your system's stack size is very limited, it might segfault on larger sorted arrays.
            copyArray(baseArr, testArr, n);
            if ((t == 1 || t == 2) && n > 20000) {
                // Skips to avoid stack overflow crashes during recursive calls on deep O(n) call stacks
                t_quick = -1.0;
            } else {
                t_quick = measureQuickSortTime(testArr, n);
            }

            // 5. Merge Sort
            copyArray(baseArr, testArr, n);
            t_merge = measureMergeSortTime(testArr, n);

            // 6. Heap Sort
            copyArray(baseArr, testArr, n);
            t_heap = measureTime(heapSort, testArr, n);

            // Print row formatted clean for easy reading/extraction
            printf("%d\t%.2f\t%.2f\t\t%.2f\t\t%.2f\t%.2f\t%.2f\n",
                    n, t_bubble, t_insert, t_select, t_quick, t_merge, t_heap);

            // NEW: log the same row to results.csv
            fprintf(csv, "%s,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                    inputTypes[t], n, t_bubble, t_insert, t_select, t_quick, t_merge, t_heap);
            fflush(csv);

            free(baseArr);
            free(testArr);
        }
        printf("\n");
    }

    // NEW: close the csv file
    fclose(csv);

    return 0;
}
