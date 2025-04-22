#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sigint(int sig) {
    printf("Help! I've been shot!\n");
    fflush(stdout);
    exit(EXIT_SUCCESS);
}

int main(void) {
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("signal");
        return EXIT_FAILURE;
    }


    while (1) {
        pause();
    }

    return EXIT_SUCCESS;
}
