#include<stdio.h>

int bitXOR(int x, int y) {
  return ~( ~(x & ~y) & ~(~x & y) );
}


int main() {

    int a = 5;
    int b = 4;

    printf("%d \n", bitXOR(a, b));


    return 0;
}