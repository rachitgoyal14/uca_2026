#include <stdio.h>


// F => FROM
// T => TO
// H => Helper

int steps = 0;

void toh(int n, char F, char T, char H) {
    
    if (n == 0) return;
    
    toh(n - 1, F, H, T);

    steps++;
    printf("%d: %c - %c\n", steps, F, T);

    toh(n - 1, H, T, F);

}


int main() {

    toh(3, 'A', 'C', 'B');

    return 0;
}

