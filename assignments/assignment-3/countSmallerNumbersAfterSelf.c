#include <stdio.h>

void merge(int nums[], int index[], int l, int m, int r, int answer[]) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Temporary arrays
    int L[n1], R[n2];
    int Lidx[n1], Ridx[n2];

    // Fill temporary arrays
    int k = l;
    for (int i = 0; i < n1; i++) {
        L[i] = nums[k];
        Lidx[i] = index[k];
        k++;
    }

    for (int i = 0; i < n2; i++) {
        R[i] = nums[k];
        Ridx[i] = index[k];
        k++;
    }

    // Merge
    int i = 0, j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            answer[Lidx[i]] += j;

            nums[k] = L[i];
            index[k] = Lidx[i];
            i++;
        } else {
            nums[k] = R[j];
            index[k] = Ridx[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        answer[Lidx[i]] += j;

        nums[k] = L[i];
        index[k] = Lidx[i];
        i++;
        k++;
    }

    while (j < n2) {
        nums[k] = R[j];
        index[k] = Ridx[j];
        j++;
        k++;
    }
}

void mergeSort(int nums[], int index[], int l, int r, int answer[]) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;

    mergeSort(nums, index, l, m, answer);
    mergeSort(nums, index, m + 1, r, answer);

    merge(nums, index, l, m, r, answer);
}

void countSmaller(int nums[], int n, int answer[]) {
    int index[n];

    // Initialize
    for (int i = 0; i < n; i++) {
        answer[i] = 0;
        index[i] = i;
    }

    mergeSort(nums, index, 0, n - 1, answer);
}

int main() {
    int nums[] = {5, 2, 6, 1};
    int n = sizeof(nums) / sizeof(nums[0]);

    int answer[n];

    countSmaller(nums, n, answer);

    printf("Answer: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", answer[i]);
    }
    printf("\n");

    return 0;
}