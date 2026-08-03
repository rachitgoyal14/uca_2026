#include<stdio.h>

int bitAnd(int x, int y) {
  return ~(~x | ~y);
}

int main() {

    int a = 5;
    int b = 6;

    printf("%d \n", bitAnd(a, b));


    return 0;
}