include<stdio.h>


int bruteForceSolution(int nums[], int n) {
	int count = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (nums[i] > 2 * nums[j]) count++;
		}	
	}

	return count;

}




int main() {

	int arr[] = {1, 3, 2, 3, 1};
	printf("%d \n", bruteForceSolution(arr, 5));



   	return 0;
}
