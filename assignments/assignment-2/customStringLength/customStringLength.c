#include <stdio.h>

int my_strlen(const char *str) {
    int length = 0;

    while (str[length] != '\0') { 
        // a string is an array of characters in C
        // and each array ends with a null character, '\0'
        // so we traverse the string until we reach this null character
        length++;
    }

    return length;
}

int main() {
    const char *sample = "C,C++,Java,Python,Rust";

    printf("Length: %d\n", my_strlen(sample));
    
    return 0;
}