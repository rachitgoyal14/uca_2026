#include<stdio.h>


int sign(int x) {
    return (x >> 31) | (!!x);
}

int main() {

    printf("%d \n", sign(-23));

    return 0;
}