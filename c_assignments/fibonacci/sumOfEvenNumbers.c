#include <stdio.h>

int sumOfEvenTermsInFibonacci(int n) {
    int a = 0, b = 1, next;
    int sumOfEvenTerms = 0;

    for (int i = 0; i < n; i++) {
        if (a % 2 == 0) {
            sumOfEvenTerms += a;
        }

        next = a + b;
        a = b;
        b = next;
    }

    return sumOfEvenTerms;
}

int main() {
    int n;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    int sumOfEvenTerms = sumOfEvenTermsInFibonacci(n);

    printf("Sum of even Fibonacci terms = %d\n", sumOfEvenTerms);

    return 0;
}