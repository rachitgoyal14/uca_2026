#include <stdio.h>

int find_substring(const char *haystack, const char *needle) {
    int i = 0; // traverse the haystack string

    while (haystack[i] != '\0') {
        int j = 0; // traverse the needle string

        // // trying to match the needle's starting at haystack[i]
        while (needle[j] != '\0' && haystack[i + j] == needle[j]) {
            j++; // move j to the next index if the characters at that index match
        }

        // // if we walked until the end of the needle, it just means that every character matched
        if (needle[j] == '\0') {
            return i;
        }

        i++;
    }

    return -1; // not found
}

int main() {
    const char *haystack = "Embedded Systems";
    const char *needle = "bed";

    int result = find_substring(haystack, needle);

    if (result != -1) {
        printf("Found at index: %d\n", result);
    } else {
        printf("Not found\n");
    }

    return 0;
}