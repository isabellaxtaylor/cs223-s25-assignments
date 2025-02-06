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
    int total_len = s_len * n + 1;

    char *repeated = (char *)malloc(total_len * sizeof(char));

    if (repeated == NULL) {
        printf("Cannot allocate new string.\n");
        return;
    }

    repeated[0] = '\0';
    for (int i = 0; i < n; i++) {
        strcat(repeated, s);
    }

    printf("%s\n", repeated);

    free(repeated);
}

int main() {
    char s[32];
    int n;

    printf("Enter a word: ");
    scanf("%31s", s);

    printf("Enter a count: ");
    scanf("%d", &n);
        if (scanf("%d", &n) != 1) {
        printf("Invalid input. Not a number.\n");
        return 1;
    }

    repeat(s, n);

    return 0;
}
