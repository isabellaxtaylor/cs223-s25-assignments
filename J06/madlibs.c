#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 32


int main(void) {
    int boolean;
    int num;

    printf("Enter a boolean (0 or 1): ");
    if (scanf("%d", &boolean) != 1) {
        fprintf(stderr, "Invalid input for boolean.\n");
        return 1;
    }

    printf("Enter number of adjectives: ");
    if (scanf("%d", &num) != 1 || num <= 0) {
        fprintf(stderr, "Invalid number of adjectives.\n");
        return 1;
    }

    getchar();

    char **adjs = malloc(num * sizeof(char *));
    if (!adjs) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < num; i++) {
        adjs[i] = malloc(32);
        if (!adjs[i]) {
            fprintf(stderr, "Memory allocation failed.\n");
            return 1;
        }
        printf("Enter adjective %d: ", i + 1);
        if (!fgets(adjs[i], 32, stdin)) {
            fprintf(stderr, "Error reading adjective.\n");
            return 1;
        }
        size_t len = strlen(adjs[i]);
        if (len > 0 && adjs[i][len - 1] == '\n') {
            adjs[i][len - 1] = '\0';
        }
    }

    printf("You are the most ");
    for (int i = num - 1; i >= 0; i--) {
        printf("%s", adjs[i]);
        if (i > 1) {
            printf(", ");
        } else if (i == 1) {
            printf(", and ");
        }
    }
    printf(" person that I know and you know its %s!\n",
           boolean ? "true" : "false");

    for (int i = 0; i < num; i++) {
        free(adjs[i]);
    }
    free(adjs);

    return 0;
}

