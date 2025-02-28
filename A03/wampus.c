/*----------------------------------------------
 * wampus.c
 * Author: Isabella Taylor
 * Date: 02/06/2025
 * Description: generates an NxM grid, randomly 
 * places a Wampus, and fills the remaining cells 
 * with their Manhattan distances from the Wampus 
 * using dynamic memory allocation. This program uses 
 * command-line arguments to get the grid size, but 
 * prompts the user for input if no arguments are given.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **allocateGrid(int rows, int cols) {
    char **grid = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        grid[i] = (char *)malloc(cols * sizeof(char));
    }
    return grid;
}

void freeGrid(char **grid, int rows) {
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}

int main() {
    int rows, cols;
    
    printf("Number of rows: ");
    scanf("%d", &rows);
    printf("Number of columns: ");
    scanf("%d", &cols);

    char **grid = allocateGrid(rows, cols);

    srand(time(NULL));

    int wampusRow = rand() % rows;
    int wampusCol = rand() % cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == wampusRow && j == wampusCol) {
                grid[i][j] = 'W';
            } else {
                grid[i][j] = '0' + abs(i - wampusRow) + abs(j - wampusCol);
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }

    freeGrid(grid, rows);

    return 0;
}