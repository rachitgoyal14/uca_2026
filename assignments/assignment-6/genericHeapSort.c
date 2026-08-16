#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(void *a, int i, int j, int size);
void sink(void *a, int i, int n, int (*cmp)(void *, void *), int size);
void heapify(void *a, int n, int (*cmp)(void *, void *), int size);
void heap_sort(void *a, int n, int (*cmp)(void *, void *), int size);
int cmp_int(void *a, void *b);
int cmp_double(void *a, void *b);
void print_int(int a[], int n);
void print_double(double a[], int n);

void swap(void *a, int i, int j, int sz){
    
    // malloc returns void* pointer
    // allot sz slots of memory to temp
    char *temp = malloc(sz); 


    // use char* pointer to fetch individual memory slots.
    // why char? => char is the only byte to byte pointer
    char *t1 = (char *)(a + i * sz);
    char *t2 = (char *)(a + j * sz);

    // usual swap stuff
    // except in this case, we are toying around with the actual memory of the system
    memcpy(temp, t1, sz);
    memcpy(t1, t2, sz);
    memcpy(t2, temp, sz);

    free(temp);
}

void sink(void *a, int i, int n, int (*cmp)(void *, void *), int sz) {
    
    int L = 2 * i + 1; // left child of current node => (2 * index of that node) + 1
    int R = 2 * i + 2;  // right child of current node => (2 * index of that node) + 2
    int max = i; 

    if (L < n && cmp(a + L * sz, a + max * sz) > 0)
        max = L;

    if (R < n && cmp(a + R * sz, a + max * sz) > 0)
        max = R;

    if (max != i) {
        swap(a, i, max, sz);
        sink(a, max, n, cmp, sz);
    }
}

void heapify(void *a, int n, int (*cmp)(void *, void *), int sz) {
    for (int i = n / 2; i >= 0; i--)
        sink(a, i, n, cmp, sz);
}

void heap_sort(void *a, int n, int (*cmp)(void *, void *), int sz) {
    heapify(a, n, cmp, sz);

    for (int i = n - 1; i > 0; i--) {
        swap(a, 0, i, sz);
        sink(a, 0, i, cmp, sz);
    }
}

// comparator functions 

// comparator for integer datatype
int cmp_int(void *a, void *b) {
    int x = *(int *)a;
    int y = *(int *)b;

    return (x > y) - (x < y);   // 1, 0, -1 
}


// comparator for double datatype
int cmp_double(void *a, void *b) {
    double x = *(double *)a;
    double y = *(double *)b;
    return (x > y) - (x < y);
}

// lets do some testing 

void print_int(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void print_double(double a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%.2f ", a[i]);
    printf("\n");
}

int main() {

    // demo with integer
    int a[] = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6};
    int n = sizeof(a) / sizeof(a[0]);

    printf("Before: ");
    print_int(a, n);

    heap_sort(a, n, cmp_int, sizeof(int));

    printf("After:  ");
    print_int(a, n);



    // demo with double
    double d[] = {3.14, 2.71, 1.41, 1.73, 0.57};
    int nd = sizeof(d) / sizeof(d[0]);

    printf("\nBefore: ");
    print_double(d, nd);

    heap_sort(d, nd, cmp_double, sizeof(double));

    printf("After:  ");
    print_double(d, nd);

    return 0;
}