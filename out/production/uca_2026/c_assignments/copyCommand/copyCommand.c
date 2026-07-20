#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int inputFd, outputFd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        printf("Error opening input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    outputFd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (outputFd == -1) {
        printf("Error opening output file %s\n", argv[2]);
        close(inputFd);
        exit(EXIT_FAILURE);
    }

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        if (write(outputFd, buf, numRead) != numRead) {
            printf("Error writing to output file %s\n", argv[2]);
            close(inputFd);
            close(outputFd);
            exit(EXIT_FAILURE);
        }
    }

    close(inputFd);
    close(outputFd);

    return 0;
}
