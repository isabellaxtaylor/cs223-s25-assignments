#include <stdio.h>
#include <string.h>

void sort_digits(char *digits) {
    char temp;
    int n = strlen(digits);
    
    for (int i = 0; i < n; i++) {
        for (int x = i + 1; x < n; x++) {
            if (digits[i] > digits[x]) {
                temp = digits[i];
                digits[i] = digits[x];
                digits[x] = temp;
            }
        }
    }
    printf("%s\n", digits);
}

int main() {
    char input[100];
    printf("Enter digits: ");
    scanf("%s", input);
    sort_digits(input);
    return 0;
}