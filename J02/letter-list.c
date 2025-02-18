#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Word {
    struct Word *next;
    char word[31];
    char letter;
} Word;

void remove_letter(Word **head, char *modifiedWord, char letter) {
    Word *new_word = malloc(sizeof(Word));
    strcpy(new_word->word, modifiedWord);
    new_word->letter = letter;
    new_word->next = NULL;
    *head = new_word;
}

void printWord(Word *head) {
    while (head) {
        printf("%s", head->word);
        head = head->next;
    }
    printf("\n");
}

void clear(Word **head) {
    while (*head) {
        Word *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    Word *head = NULL;
    char word[31];
    char letter;

    printf("Enter a word: ");
    scanf("%30s", word);
    printf("Enter a character to remove: ");
    scanf(" %c", &letter);
    
    int length = strlen(word);
    char* newWord = malloc((length + 1) * sizeof(char));
    
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (word[i] != letter) {
            newWord[j++] = word[i];
        }
    }
    newWord[j] = '\0';

    remove_letter(&head, newWord, letter);
    
    printWord(head);
    clear(&head);

    free(newWord);
    
    return 0;
}