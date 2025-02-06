/*----------------------------------------------
 * dynamic_snacks.c
 * Author: Isabella Taylor
 * Date: 02/06/2025 
 * Description: allows the user to input snack details (name, price, and quantity) and displays the information
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int numSnacks;
    
    printf("Enter the number of snacks: ");
    scanf("%d", &numSnacks);

    char **snacks = (char **)malloc(numSnacks * sizeof(char *));
    float *price = (float *)malloc(numSnacks * sizeof(float));
    int *quantity = (int *)malloc(numSnacks * sizeof(int));

    if (snacks == NULL || price == NULL || quantity == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < numSnacks; i++) {
        snacks[i] = (char *)malloc(100 * sizeof(char));  
        if (snacks[i] == NULL) {
            printf("Memory allocation failed for snack name.\n");
            return 1;
        }

        printf("\nEnter the name of snack %d: ", i + 1);
        scanf("%s", snacks[i]);
        
        printf("Enter the cost of %s: $", snacks[i]);
        scanf("%f", &price[i]);
        
        printf("Enter the quantity of %s: ", snacks[i]);
        scanf("%d", &quantity[i]);
    }

    printf("\nWelcome to Dynamic Donna's Snack Bar.\n");
    for (int i = 0; i < numSnacks; i++) {
        printf("%d) %s      cost: $%.2f     quantity: %d\n", i + 1, snacks[i], price[i], quantity[i]);
    }

    for (int i = 0; i < numSnacks; i++) {
        free(snacks[i]);
    }
    free(snacks);
    free(price);
    free(quantity);

    return 0;
}
