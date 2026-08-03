#include <stdio.h>

int getByte(int x, int n) {
    return (x >> (n << 3)) & 0xFF;
}

int main(void) {
    
    printf("getByte(0x12345678,1)  = 0x%X\n", getByte(0x12345678, 1));
    printf("getByte(0x12345678,0)  = 0x%X\n", getByte(0x12345678, 0));
    printf("getByte(0x12345678,3)  = 0x%X\n", getByte(0x12345678, 3));

    return 0;
}