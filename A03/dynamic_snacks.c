/*----------------------------------------------
 * dynamic_snacks.c
 * Author: Isabella Taylor
 * Date: 02/06/2025 
 * Description: allows the user to input snack details (name, price, and quantity) and displays the information
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[100];
    float price;
    int quantity;
} Snack;

int main() {
    int numSnacks;
    
    printf("Enter a number of snacks: ");
    scanf("%d", &numSnacks);

    Snack *snacks = (Snack *)malloc(numSnacks * sizeof(Snack));
    if (snacks == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < numSnacks; i++) {
        printf("\nEnter a name: ");
        scanf("%s", snacks[i].name);
        
        printf("Enter a cost: ");
        scanf("%f", &snacks[i].price);
        
        printf("Enter a quantity: ");
        scanf("%d", &snacks[i].quantity);
    }

    printf("\nWelcome to Dynamic Donna's Snack Bar.\n\n");
    for (int i = 0; i < numSnacks; i++) {
        printf("%d) %-20s cost: $%.2f     quantity: %d\n", 
               i, snacks[i].name, snacks[i].price, snacks[i].quantity);
    }

    free(snacks);
    return 0;
}
