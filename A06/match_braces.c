/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 2/28/2025
 * Description: Checks for matching braces in a file.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

// Structure for  stack
typedef struct {
    int line;
    int col;
} BracePos;

// Stack for storing braces' positions
BracePos stack[MAX_STACK_SIZE];
int top = -1;

// Function to push element onto stack
void push(int line, int col) {
    if (top < MAX_STACK_SIZE - 1) {
        top++;
        stack[top].line = line;
        stack[top].col = col;
    } else {
        printf("Stack overflow\n");
        exit(1);
    }
}

// Function to pop element from stack
BracePos pop() {
    if (top >= 0) {
        return stack[top--];
    } else {
        printf("Stack underflow\n");
        exit(1);
    }
}


void match_braces(FILE *file) {
    int lineNum = 1, colNum = 1;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '{') {
            // Push  position of '{' onto stack
            push(lineNum, colNum);
        } else if (ch == '}') {
            // Check if there's a matching '{'
            if (top >= 0) {
                BracePos matchingBrace = pop();
                printf("Found matching braces: (%d, %d) -> (%d, %d)\n",
                        matchingBrace.line, matchingBrace.col, lineNum, colNum);
            } else {
                printf("Unmatched brace on Line %d and Column %d\n", lineNum, colNum);
            }
        }

        // Update column number for each character
        if (ch == '\n') {
            lineNum++;
            colNum = 1;
        } else {
            colNum++;
        }
    }

    // If there are any unmatched '{' left in the stack
    while (top >= 0) {
        BracePos unmatchedBrace = pop();
        printf("Unmatched brace on Line %d and Column %d\n", unmatchedBrace.line, unmatchedBrace.col);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Cannot open file: %s\n", argv[1]);
        return 1;
    }

    match_braces(file);

    fclose(file);
    return 0;
}
