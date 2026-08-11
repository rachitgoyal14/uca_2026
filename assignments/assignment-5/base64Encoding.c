#include <stdio.h>
#include <string.h>

void base64_encode(char *input, char *output);
int char_to_value(char c);
void base64_decode(char *input, char *output);

// the 64 characters being used for base64 encoding
char b64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// encode text into base64
void base64_encode(char *input, char *output) {
    
    int input_len = strlen(input);
    int j = 0;  // index for iterating in the output

    for (int i = 0; i < input_len; i = i + 3) {
        // graph upto the maximum of 3 bytes and pad the remaining ones with 0
        
        int byte1 = input[i];
        int byte2 = 0;
        int byte3 = 0;

        if (i + 1 < input_len) {
            byte2 = input[i + 1];
        }
        if (i + 2 < input_len) {
            byte3 = input[i + 2];
        }

        // combine the 3 bytes into 24 bits
        int combined = (byte1 << 16) + (byte2 << 8) + byte3;

        // split into chunks of 4
        // lookup the ASCII values of each chunk
        output[j]     = b64_chars[(combined >> 18) & 63];
        output[j+1] = b64_chars[(combined >> 12) & 63];
        output[j+2] = b64_chars[(combined >> 6) & 63];
        output[j+3] = b64_chars[combined & 63];

        // if only a single byte existed
        // pad with 0s

        if (i + 1 >= input_len) {
            output[j + 2] = '=';
        }
        if (i + 2 >= input_len) {
            output[j + 3] = '=';
        }

        j = j + 4;
    }

    output[j] = '\0';  // add null character to denote the end of the string
}

// change a base64 value into its original 64 bit value (from 0 to 64)
int char_to_value(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';           // A=0, B=1, ... Z=25
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;      // a=26, b=27, ... z=51
    }
    if (c >= '0' && c <= '9') {
        return c - '0' + 52;      // 0=52, 1=53, ... 9=61
    }
    if (c == '+') {
        return 62;
    }
    if (c == '/') {
        return 63;
    }
    return 0;  // '=' or anything else, just treat as 0
}

// decode a base64 string back into the original text
void base64_decode(char *input, char *output) {
    int input_len = strlen(input);
    int j = 0;  // index into output

    for (int i = 0; i < input_len; i = i + 4) {

        // read 4 base64 characters at a time
        int value1 = char_to_value(input[i]);
        int value2 = char_to_value(input[i+1]);
        int value3 = char_to_value(input[i+2]);
        int value4 = char_to_value(input[i+3]);

        // put the four 6-bit values back together into 24 bits
        int combined = (value1 << 18) + (value2 << 12) + (value3 << 6) + value4;

        // pull out the three original bytes
        char byte1 = (combined >> 16) & 255;
        char byte2 = (combined >> 8) & 255;
        char byte3 = combined & 255;

        output[j] = byte1;
        j = j + 1;

        // only add byte2 if this group wasn't padded with '='
        if (input[i + 2] != '=') {
            output[j] = byte2;
            j = j + 1;
        }

        // only add byte3 if this group wasn't padded with '='
        if (input[i + 3] != '=') {
            output[j] = byte3;
            j = j + 1;
        }
    }

    output[j] = '\0';  // end the string using null character
}

int main() {
    char original[] = "hahahahha lol asdnaksdkj as kaskj dkas dl aosdbf";
    char encoded[2000];
    char decoded[2000];

    // testing the encoded one
    base64_encode(original, encoded);
    printf("Original: %s\n", original);
    printf("Encoded:  %s\n", encoded);

    // testing the decoded one
    base64_decode(encoded, decoded);
    printf("Decoded:  %s\n", decoded);

    return 0;
}