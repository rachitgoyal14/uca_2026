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

int main() {
    srand(time(NULL)); // seed for random generation

    int sizes[] = {8000, 12000, 16000, 20000, 24000, 28000, 32000, 36000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("--- HEAP SORT BENCHMARK RESULTS (Time in Milliseconds) ---\n\n");

    // results.csv so the numbers can be pivoted/plotted directly, instead of re-typing terminal output
    FILE* csv = fopen("heapsort_results.csv", "w");
    fprintf(csv, "InputType,Size,Heap\n");

    const char* inputTypes[] = {"Random", "Ascending", "Descending"};

    for (int t = 0; t < 3; t++) {
        printf("==================================================\n");
        printf(" INPUT TYPE: %s\n", inputTypes[t]);
        printf("==================================================\n");
        printf("Size\tHeap\n");

        for (int s = 0; s < numSizes; s++) {
            int n = sizes[s];

            // allocate memory dynamically to prevent stack overflows
            int* baseArr = (int*)malloc(n * sizeof(int));
            int* testArr = (int*)malloc(n * sizeof(int));

            // generate the required array layout
            if (t == 0) generateRan(baseArr, n);
            else if (t == 1) generateAsc(baseArr, n);
            else generateDesc(baseArr, n);

            double t_heap;

            // Heap Sort
            copyArray(baseArr, testArr, n);
            t_heap = measureTime(heapSort, testArr, n);

            // Print row formatted clean for easy reading/extraction
            printf("%d\t%.2f\n", n, t_heap);

            // log the same row to heapsort_results.csv
            fprintf(csv, "%s,%d,%.2f\n", inputTypes[t], n, t_heap);
            fflush(csv);

            free(baseArr);
            free(testArr);
        }
        printf("\n");
    }

    // close the csv file
    fclose(csv);

    return 0;
}