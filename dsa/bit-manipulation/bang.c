#include <stdio.h>


int bang(int x) {
    return ((x | (~x + 1)) >> 31) + 1;
}


int main() {

    printf("bang(3) = %d (0x%X)\n", bang(3), bang(3));
    printf("bang(0) = %d (0x%X)\n", bang(0), bang(0));

    return 0;
}