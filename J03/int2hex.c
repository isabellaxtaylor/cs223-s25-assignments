#include <stdio.h>
#include <stdlib.h>

void print_binary(int value) {
    int size = 32; 
    printf("0b ");

    for (int i = size - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);

        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }

    printf("\n");
}

void print_hex(int value) {
    int size = 8;
    printf("0x ");

    for (int i = size - 1; i >= 0; i--) {
        int digit = (value >> (i * 4)) & 0xF;
        printf("%X", digit);

        if (i % 2 == 0 && i != 0) {
            printf(" ");
        }
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);
    print_binary(value);
    print_hex(value);
    return 0;
}
