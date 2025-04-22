#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int  c;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while ((c = fgetc(fp)) != EOF) {
        unsigned char usignc = (unsigned char)c;
        usignc = (usignc >> 1) & 0x7F;
        putchar(usignc);
    }

    fclose(fp);
    return EXIT_SUCCESS;
}
