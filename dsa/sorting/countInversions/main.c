#include<stdio.h>
int bruteForceSolution(int nums[], int n);
void merge(int nums[], int l, int m, int r);
void mergeSort(int nums[], int l, int r);
int optimizedApproach(int nums[], int n);


// TIME COMPLEXITY: O (N^2)
int bruteForceSolution(int nums[], int n) {
	int count = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (nums[i] > nums[j]) count++;
		}	
    }

	return count;

}
// // ----------------------------------OPTIMIZED SOLUTION ------------------------------------------------

// TIME COMPLEXITY: O(N*log(N))
// MERGE SORT HEHE

// // global variable count
int count = 0;

void merge(int nums[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int k = l; // index to traverse the original array and fill up the values in the temporary one

    // create temporary arrays
    int L[n1];
    int R[n2];

    // fill up those temporary arrays
    for (int i = 0; i < n1; i++) L[i] = nums[k++];
    for (int j = 0; j < n2; j++) R[j] = nums[k++];

    // merge elements from the temporary arrays into the original ones
    int i = 0, j = 0;
    k = l; // iterator to set values into the original array

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) nums[k++] = L[i++];
        else {
            nums[k++] = R[j++];
            // count the number of inversions in the arrya
            count += n1 - i;
            }
    }

    // 'i' got out of bounds
    while (j < n2) nums[k++] = R[j++];
    while (i < n1) nums[k++] = L[i++];
}

void mergeSort(int nums[], int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;

    mergeSort(nums, l, m);
    mergeSort(nums, m + 1, r);
    merge(nums, l, m, r);
}

int optimizedApproach(int nums[], int n) {
    count = 0;
    mergeSort(nums, 0, n - 1);
    return count;
}


int main() {

	int arr[] = {1, 2, 4, 1, 4, 5};
	// printf("%d \n", bruteForceSolution(arr, 5));
    printf("%d \n", optimizedApproach(arr, 6));


   	return 0;
}
