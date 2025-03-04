#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *hex_digits = "0123456789abcdef";

int convert_binary(const char *bin) {
    int value = 0;
    while (*bin) {
        value = (value << 1) | (*bin - '0');
        bin++;
    }
    return value;
}

int convert_hex(const char *hex) {
    int value = 0;
    while (*hex) {
        char c = *hex;
        const char *ptr = strchr(hex_digits, tolower(c));

        if (!ptr) {
            printf("Invalid hex character: %c\n", c);
            exit(1);
        }

        int bitVal = ptr - hex_digits; 
        value = (value << 4) | bitVal;
        hex++;
    }
    return value;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <hexadecimal or binary number>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];
    int value = 0;

    if (strncmp(input, "0x", 2) == 0 || strncmp(input, "0X", 2) == 0) {
        value = convert_hex(input + 2);
    } else if (strncmp(input, "0b", 2) == 0 || strncmp(input, "0B", 2) == 0) {
        value = convert_binary(input + 2);
    } else {
        printf("Invalid format. Use 0x for hex and 0b for binary.\n");
        return 1;
    }

    printf("%d\n", value);
    return 0;
}
