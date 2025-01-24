/***************************************************
 * mathgame.c
 * Author: Isabella Taylor
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
    
int main() {
    srand(time(NULL));
    
    printf("Welcome to Math Game!\n");
    
    int mathQuestion;
    printf("How many rounds do you want to play? ");
    scanf("%d",&mathQuestion);
    
    int correctMath=0;
    
    for (int i = 0; i < mathQuestion; i++) {
        int num1=rand()%9+1;
        int num2=rand()%9+1;
        
        printf("%d + %d = ? ", num1, num2);
        int userResponse;
        scanf("%d",&userResponse);
        
        if (userResponse==num1+num2){
            printf("Correct!\n");
            correctMath++;
        } else {
            printf("Incorrect:(\n");
        }
    }
    printf("You answered %d/%d correctly.\n",correctMath,mathQuestion);
  return 0;
}
