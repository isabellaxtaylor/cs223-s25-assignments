/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 3/28/2025
 * Description: Multi-Process Keyword Search.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <NumProcesses> <keyword> <files>\n", argv[0]);
        return 1;
    }

    int numProcs = atoi(argv[1]);
    char *keyword = argv[2];
    int numFiles = argc - 3;
    char **files = &argv[3]; 

    struct timeval start, end;
    gettimeofday(&start, NULL);

    int baseCount = numFiles / numProcs; 
    int remainder = numFiles % numProcs;

    pid_t *pids = malloc(numProcs * sizeof(pid_t));
    if (!pids) {
        perror("malloc");
        return 1;
    }

    int fileIndex = 0;
    for (int i = 0; i < numProcs; i++) {
        int count = baseCount + ((i < remainder) ? 1 : 0);
        int startIndex = fileIndex;
        int endIndex = fileIndex + count;

        fileIndex = endIndex; 

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            free(pids);
            return 1;
        }
        if (pid == 0) {
            int occurrences = 0;

            printf(ANSI_COLOR_GREEN "Process [%d] searching %d file(s)...\n" ANSI_COLOR_RESET,
                   getpid(), count);

            for (int f = startIndex; f < endIndex; f++) {
                FILE *fp = fopen(files[f], "r");
                if (!fp) {
                    fprintf(stderr, ANSI_COLOR_RED
                            "Process [%d] ERROR: Cannot open file %s\n"
                            ANSI_COLOR_RESET, getpid(), files[f]);
                    continue;
                }

                char line[1024];
                while (fgets(line, sizeof(line), fp)) {
                    if (strstr(line, keyword) != NULL) {
                        occurrences++;
                    }
                }
                fclose(fp);
            }

            _exit(occurrences % 256);
        } else {
            pids[i] = pid;
        }
    }

    int totalOccurrences = 0;
    for (int i = 0; i < numProcs; i++) {
        int status;
        waitpid(pids[i], &status, 0);
        if (WIFEXITED(status)) {
            int childCount = WEXITSTATUS(status);
            totalOccurrences += childCount;
        }
    }

    free(pids);

    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec)
                     + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("Total occurrences: %d\n", totalOccurrences);
    printf("Elapsed time is %f seconds\n", elapsed);

    return 0;
}
