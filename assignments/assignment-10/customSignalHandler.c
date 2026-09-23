#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void sigHandler(int sig) {
    static int count = 0;

    if (sig == SIGINT) {
        count++;
        printf("   Ctrl + C Pressed => Caught SIGINT (%d)\n", count);

        if (count == 3) {
            printf("Exiting...\n");
            exit(0);
        }
        return;
    }
}

int main() {
    if (signal(SIGINT, sigHandler) == SIG_ERR) {
        exit(-1);
    }

    printf("Program running (PID: %d). Try pressing Ctrl+C...\n", getpid());

    for (;;)
        pause();

    return 0;
}