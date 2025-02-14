/*----------------------------------------------
 * Author: 
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Snack {
    struct Snack *next;
    char name[50];
    float cost;
    int quantity;
} Snack;

// Function to create a new snack node
struct Snack* create_snack(char *name, float cost, int quantity) {
    struct Snack* new_snack = malloc(sizeof(struct Snack));
    if (new_snack==NULL) {
        printf("ERROR: Out of space!\n");
        exit(1);
    }
    strcpy(new_snack->name, name);
    new_snack->cost = cost;
    new_snack->quantity = quantity;
    return new_snack;
}

// Function to insert a snack at the beginning of the list
void insert_first(Snack **head, char *name, float cost, int quantity) {
    Snack *new_snack = create_snack(name, cost, quantity);
    new_snack->next = *head;
    *head = new_snack;
}

// Function to print the snack list
void printList(Snack *head) {
    printf("\nWelcome to Sorted Sally's Snack Bar.\n\n");
    int index = 0;
    while (head) {
        printf("%d) %-20s cost: $%.2f     quantity: %d\n", index, head->name, head->cost, head->quantity);
        head = head->next;
        index++;
    }
}

// Function to clear and free all items in the list
void clear(Snack **head) {
    Snack *temp;
    while (*head) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

// Function to sort by cost
void sortCost(Snack **head) {
    if (*head == NULL || (*head)->next == NULL) return;
    Snack *sorted = NULL;
    Snack *current = *head;
    while (current) {
        Snack *next = current->next;
        Snack **ptr = &sorted;
        while (*ptr && (*ptr)->cost < current->cost) {
            ptr = &(*ptr)->next;
        }
        current->next = *ptr;
        *ptr = current;
        current = next;
    }
    *head = sorted;
}

// Function to sort by name
void sortName(Snack **head) {
    if (*head == NULL || (*head)->next == NULL) return;
    Snack *sorted = NULL;
    Snack *current = *head;
    while (current) {
        Snack *next = current->next;
        Snack **ptr = &sorted;
        while (*ptr && strcmp((*ptr)->name, current->name) < 0) {
            ptr = &(*ptr)->next;
        }
        current->next = *ptr;
        *ptr = current;
        current = next;
    }
    *head = sorted;
}

// Function to sort by quantity
void sortQuantity(Snack **head) {
    if (*head == NULL || (*head)->next == NULL) return;
    Snack *sorted = NULL;
    Snack *current = *head;
    while (current) {
        Snack *next = current->next;
        Snack **ptr = &sorted;
        while (*ptr && (*ptr)->quantity < current->quantity) {
            ptr = &(*ptr)->next;
        }
        current->next = *ptr;
        *ptr = current;
        current = next;
    }
    *head = sorted;
}

int main() {
    Snack *head = NULL;
    int num_snacks;
    char name[50];
    float cost;
    int quantity;

    printf("Enter a number of snacks: ");
    scanf("%d", &num_snacks);

    for (int i = 0; i < num_snacks; i++) {
        printf("Enter a name: ");
        scanf("%s", name);
        printf("Enter a cost: ");
        scanf("%f", &cost);
        printf("Enter a quantity: ");
        scanf("%d", &quantity);
        insert_first(&head, name, cost, quantity);
    }

    printf("\nSorted by Name:\n");
    sortName(&head);
    printList(head);
    
    printf("\nSorted by Cost:\n");
    sortCost(&head);
    printList(head);
    
    printf("\nSorted by Quantity:\n");
    sortQuantity(&head);
    printList(head);
    
    clear(&head);
    return 0;
}