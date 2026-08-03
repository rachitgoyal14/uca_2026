#include <stdio.h>


int fitsBits(int x, int n) {
  
    int shift = 33 + ~n;        // 32 - n
    int shifted = (x << shift) >> shift;
  
    return !(shifted ^ x);
}


int main() {

    int a = 5;
    int b = 4;

    printf("%d \n", fitsBits(a, b));


    return 0;
}