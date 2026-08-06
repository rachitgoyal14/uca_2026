#include <stdio.h>

void url_encode(char *str, int true_length) {
    int spaceCount = 0;

    // // count spaces in the original string
    for (int i = 0; i < true_length; i++) {
        if (str[i] == ' ') {
            spaceCount++;
        }
    }

    // // calculate the TO BE new length after the encoding is done
    int newLength = true_length + (spaceCount * 2);

    // // traverse backwards. copying the characters into their final positions
    int writeIndex = newLength;
    str[writeIndex] = '\0';  // null character => indicates the end of the new string
    writeIndex--;

    for (int readIndex = true_length - 1; readIndex >= 0; readIndex--) {
        if (str[readIndex] == ' ') {
            str[writeIndex]     = '0';
            str[writeIndex - 1] = '2';
            str[writeIndex - 2] = '%';
            writeIndex -= 3;
        } else {
            str[writeIndex] = str[readIndex];
            writeIndex--;
        }
    }
}

// // STEPS // //
// 1. calculate the new_length which will be after the space is replaced by %20
// 2. then have two pointers => writeIndex, readIndex
// ==> readIndex traverses from the end of string ti
// 3. str[write_index] = '\0' => detects the end of the string
// 4. then traverse backwards and keep on checking for empty spaces using read_index pointer
// 5. if we find an empty space, start writing using write_index in reverse and reduce the write_index by 3 eventually


int main() {

    char str[100] = "Hello World Here";
    int true_length = 17; 

    url_encode(str, true_length);

    printf("%s\n", str);

    return 0;
}