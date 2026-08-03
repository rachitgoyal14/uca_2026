#include<stdio.h>

int conditional(int x, int y, int z) {
    int cond = !!x;
    int mask = ~cond + 1;   // all 1s if x != 0, else 0
    return (mask & y) | (~mask & z);
}


int main() {

    printf("conditional(2,4,5) = %d (0x%X)\n", conditional(2, 4, 5), conditional(2, 4, 5));
    printf("conditional(0,4,5) = %d (0x%X)\n", conditional(0, 4, 5), conditional(0, 4, 5));
 
    return 0;
}