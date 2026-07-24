#include <stdio.h>

int main() {
    int c, next;

    while ((c = getchar()) != EOF) {

        if (c == '/') {
            next = getchar();

            if (next == '/') {
                // Line comment: skip everything until newline
                while ((c = getchar()) != EOF && c != '\n') {
                    // do nothing, just skip
                }
                if (c == '\n') {
                    putchar('\n'); // keep the newline
                }
            }
            else if (next == '*') {
                // Block comment: skip until we find "*/"
                int prev = 0;
                while ((c = getchar()) != EOF) {
                    if (prev == '*' && c == '/') {
                        break; // end of comment found
                    }
                    prev = c;
                }
            }
            else {
                // Not a comment, print the '/' and the next character
                putchar(c);
                if (next != EOF) {
                    putchar(next);
                }
            }
        }
        else if (c == '"') {
            // Handle a quoted string: print everything until closing quote
            putchar(c);
            while ((c = getchar()) != EOF) {
                putchar(c);
                if (c == '\\') {
                    // Escape sequence: print next character as-is
                    c = getchar();
                    if (c != EOF) {
                        putchar(c);
                    }
                } else if (c == '"') {
                    break; // end of string
                }
            }
        }
        else if (c == '\'') {
            // Handle a character constant: print everything until closing quote
            putchar(c);
            while ((c = getchar()) != EOF) {
                putchar(c);
                if (c == '\\') {
                    // Escape sequence: print next character as-is
                    c = getchar();
                    if (c != EOF) {
                        putchar(c);
                    }
                } else if (c == '\'') {
                    break; // end of char constant
                }
            }
        }
        else {
            // regular character, just print it
            putchar(c);
        }
    }

    return 0;
}
