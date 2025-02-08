/*----------------------------------------------
 * repeat.c
 * Author: Isabella Taylor
 * Date: 02/06/2025
 * Description: repeats a given word a specified number of times
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void repeat(const char *s, int n) {
    int s_len = strlen(s);

    if (n > 0 && s_len > (2147483647 / n)) {
        printf("Cannot allocate new string. Exiting...\n");
        return;
    }

    int total_len = s_len * n + 1;
    char *repeated = (char *)malloc(total_len * sizeof(char));

    if (repeated == NULL) {
        printf("Cannot allocate new string.\n");
        return;
    }

    char *ptr = repeated;
    for (int i = 0; i < n; i++) {
        memcpy(ptr, s, s_len);
        ptr += s_len;
    }
    *ptr = '\0';

    printf("Your word is %s\n", repeated);

    free(repeated);
}

int main() {
    char s[32];
    char buffer[32];
    int n;

    printf("Enter a word: ");
    fflush(stdout);
    if (scanf("%31s", s) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    getchar();

    printf("Enter a count: ");
    fflush(stdout);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &n) != 1 || n < 0) {
        printf("Invalid input. Please enter a valid positive integer.\n");
        return 1;
    }

    repeat(s, n);

    return 0;
}