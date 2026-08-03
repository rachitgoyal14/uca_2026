#include <stdio.h>

int logicalShift(int x, int n) {
    int mask = ~(((1 << 31) >> n) << 1);
    return (x >> n) & mask;
}

int main() {

     printf("logicalShift(0x87654321,4) = 0x%X\n", logicalShift(0x87654321, 4));
    return 0;
}