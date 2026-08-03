#include <stdio.h>

int isPowerOfTwo(int x) {
    if (x <= 0) {
        return 0;
    }
    return (x & (x - 1)) == 0;
}

int main() {
    printf("Enter the value you want to check: ");

    int a = 0;
    scanf("%d", &a);

    int result = isPowerOfTwo(a);
    printf("%d\n", result);

    return 0;
}