/***************************************************
 * snackbar.c
 * Author: Isabella Taylor
 * Date: 2/1/2025
 * A simple snack bar simulation where the user can purchase items 
 * based on available money and stock.
 */
#include <stdio.h>
#include <string.h>

int main() {
    float money;
    int choice;
    float price[] = {1.50, 15.50, 0.50};
    int quantity[] = {4, 6, 0};
    char *snack[]={"Coco Puffs","Manchego cheese","Magic beans"};

    printf("Welcome to Steven Struct's Snack Bar.\n");
    printf("\nHow much money do you have? ");
    scanf("%f",&money);
    
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf("%d) %s      cost: $%.2f     quantity: %d\n", i, snack[i], price[i], quantity[i]);
    }
    
    printf("\nWhat snack would you like to buy? [0,1,2] ");
    scanf("%d", &choice);    
    if (price[choice]>money) {
        printf("You can't afford it!");
    }
    else if (quantity[choice] == 0) {
        printf("Sorry, we're out of %s.\n", snack[choice]);
    }
    else if (price[choice]<=money) {
        money-=price[choice];
        printf("You bought %s. \nYou have $%.2f left.", snack[choice],money); 
    }

    return 0;
}

