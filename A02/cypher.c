/***************************************************
 * cypher.c
 * Author: Isabella Taylor
 * Date: 1/31/2025
 * This program applies a shift cipher to a given word.
 * It shifts each letter in the word by a user-specified amount.
 * The input word must be in lowercase and contain no special characters.
 */
#include <stdio.h>
#include <string.h>

int main() {
    char word[100];
    int shift;

    printf("Enter a word: ");
    scanf("%s",word);
    
    printf("Enter a shift: ");
    scanf("%d",&shift);
    
    int n = strlen(word);

    for (int i = 0; i < n; i++) {
        word[i] = ((word[i] - 'a' + shift) % 26 + 26) % 26 + 'a';
    }
    printf("Your cypher is %s\n", word);  

    return 0;
}
