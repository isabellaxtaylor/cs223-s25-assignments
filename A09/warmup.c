/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 3/28/2025
 * Description: Forked Process Spawning and PID Output.
 ---------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t ret;

    printf("%d] A0\n", getpid());

    ret = fork();

    if (ret == 0) {
        printf("%d] B1\n", getpid());
    } else {
        printf("%d] B0\n", getpid());

        ret = fork();
        if (ret == 0) {
            printf("%d] C1\n", getpid());
        } else {
            printf("%d] C0\n", getpid());
        }
    }

    printf("%d] Bye\n", getpid());
    return 0;
}
