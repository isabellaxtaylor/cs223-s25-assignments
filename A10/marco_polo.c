/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 04/04/2025
 * Description: Signals to coordinate between parent and child.
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_pid;

void parent_handler(int signum) {
    if (signum == SIGALRM) {
        printf("Polo\n");
        fflush(stdout);
    }
}

void child_handler(int signum) {
    if (signum == SIGALRM) {
        printf("Marco\n");
        fflush(stdout);
        kill(getppid(), SIGALRM);
    }
}

int main(void) {
    struct sigaction sa_parent, sa_child;

    sa_parent.sa_handler = parent_handler;
    sigemptyset(&sa_parent.sa_mask);
    sa_parent.sa_flags = 0;
    if (sigaction(SIGALRM, &sa_parent, NULL) == -1) {
        perror("sigaction (parent)");
        exit(EXIT_FAILURE);
    }

    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        sa_child.sa_handler = child_handler;
        sigemptyset(&sa_child.sa_mask);
        sa_child.sa_flags = 0;
        if (sigaction(SIGALRM, &sa_child, NULL) == -1) {
            perror("sigaction (child)");
            exit(EXIT_FAILURE);
        }

        while (1) {
            pause();
        }
        exit(EXIT_SUCCESS);
    } else {
        int c;
        printf("Enter 'm' to signal or 'q' to quit:\n");

        while ((c = getchar()) != EOF) {
            if (c == 'm') {
                kill(child_pid, SIGALRM);
            } else if (c == 'q') {
                kill(child_pid, SIGTERM);
                break;
            }
        }

        wait(NULL);
    }

    return 0;
}
