#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int winner(int a, int b, int c, int d) {
    if (a <= d && a > b && a > c) {
        return a;
    } else if (b <= d && b > a && b > c) {
        return b;
    } else if (c <= d && c > a && c > b) {
        return c;
    }
    return -1;
}

int main() {
    srand(time(0));

    int guess, guess1, guess2, cost;

    printf("Welcome to The Price is Right!\n");
    printf("Enter a guess to win a luxurious dishwasher: $");
    scanf("%d", &guess);

    guess1 = 3000 + rand() % (5000 - 3000 + 1);
    guess2 = 3000 + rand() % (5000 - 3000 + 1);
    cost = 3000 + rand() % (5000 - 3000 + 1);

    printf("AI contestant #1 guesses: $%d\n", guess1);
    printf("AI contestant #2 guesses: $%d\n", guess2);
    printf("The dishwasher cost: $%d\n", cost);

    int winning_guess = winner(guess, guess1, guess2, cost);

    if (winning_guess == guess) {
        printf("Congratulations! You won!\n");
    } else if (winning_guess == guess1) {
        printf("AI contestant #1 wins!\n");
    } else if (winning_guess == guess2) {
        printf("AI contestant #2 wins!\n");
    } else {
        printf("No one won! Everyone overbid.\n");
    }

    return 0;
}
