#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Word {
    struct Word *next;
    char word[31];
    char letter;
} Word;

void remove_letter(Word **head, char *originalWord, char letter) {
    int j = 0;
    char modifiedWord[31];

    for (int i = 0; originalWord[i] != '\0'; i++) {
        if (originalWord[i] != letter) {
            modifiedWord[j++] = originalWord[i];
        }
    }
    modifiedWord[j] = '\0';
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

    remove_letter(&head, word, letter);
    
    printWord(head);
    clear(&head);

    free(newWord);
    
    return 0;
}