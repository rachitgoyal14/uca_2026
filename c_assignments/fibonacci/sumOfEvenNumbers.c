#include <stdio.h>

// BRUTE FORCE APPROACH
// Time Complexity: O(n)
// Space Complexity: O(1)
int bruteForceSumEvenFibonacci(int n) {
    int a = 0, b = 1, next;
    int sum = 0;

    while (a <= n) {
        if (a % 2 == 0) {
            sum += a;
        }

        next = a + b;
        a = b;
        b = next;
    }

    return sum;
}

// OPTIMIZED APPROACH
// OBSERVATION => every 3rd fibonacci number is even

// Even Fibonacci recurrence:
// (next even number) = 4 * (last even number) + (second last even number)
// E(n) = 4 * E(n - 1) + E(n - 2)

// Time Complexity: O(log(N))
// Space Complexity: O(1)


int optimizedSumEvenFibonacci(int n) {
    int e1 = 0;
    int e2 = 2;
    int nextEven;
    int sum = 0;

    while (e1 <= n) {
        sum += e1; // add it to the sum

        nextEven = 4 * e2 + e1; // use the recurrence relation
        
        // move the variables to the next position
        e1 = e2; 
        e2 = nextEven;
    }

    return sum;
}

int main() {
    int n;

    printf("Enter the upper limit: ");
    scanf("%d", &n);

    printf("\nBrute Force Approach\n");
    printf("Sum of even Fibonacci numbers = %d\n",
           bruteForceSumEvenFibonacci(n));

    printf("\nOptimized Approach\n");
    printf("Sum of even Fibonacci numbers = %d\n",
           optimizedSumEvenFibonacci(n));

    return 0;
}