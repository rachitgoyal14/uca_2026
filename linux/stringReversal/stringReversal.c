#include <stdio.h>
#include <string.h>

void reverse_string(char str[]) {
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        i++;
        j--;
    }
}

int main() {
    char sample[] = "Data Structures";

    printf("Original: %s\n", sample);

    reverse_string(sample);

    printf("Reversed: %s\n", sample);

    return 0;
}