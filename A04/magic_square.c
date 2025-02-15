/*----------------------------------------------
 * magic_square.c
 * Author: Isabella Taylor
 * Date: 02/14/2025
 * Description: Program to check if a given matrix is a magic square
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int isMagicSquare(int **matrix, int dimRow) {
    int magicConstant = 0, sum;
    
    for (int valCol = 0; valCol < dimRow; valCol++) {
        magicConstant += matrix[0][valCol];
    }

    for (int valRow = 1; valRow < dimRow; valRow++) {
        sum = 0;
        for (int valCol = 0; valCol < dimRow; valCol++) {
            sum += matrix[valRow][valCol];
        }
        if (sum != magicConstant) {
          return 0;
        }
    }

    for (int valCol = 0; valCol < dimRow; valCol++) {
        sum = 0;
        for (int valRow = 0; valRow < dimRow; valRow++) {
            sum += matrix[valRow][valCol];
        }
        if (sum != magicConstant) {
          return 0;
        }
    }

    sum = 0;
    for (int valRow = 0; valRow < dimRow; valRow++) {
        sum += matrix[valRow][valRow];
    }
    if (sum != magicConstant) {
      return 0;
    }

    sum = 0;
    for (int valRow = 0; valRow < dimRow; valRow++) {
        sum += matrix[valRow][dimRow - valRow - 1];
    }
    if (sum != magicConstant) {
      return 0;
    }
    return magicConstant; 
}

int main() {
    int dimRow, dimCol;
    
    scanf("%d %d", &dimRow, &dimCol);
    
    int **matrix = malloc(dimRow * sizeof(int *));
    for (int valRow = 0; valRow < dimRow; valRow++) {
        matrix[valRow] = malloc(dimRow * sizeof(int));
    }

    for (int valRow = 0; valRow < dimRow; valRow++) {
        for (int valCol = 0; valCol < dimRow; valCol++) {
            scanf("%d", &matrix[valRow][valCol]);
        }
    }

    printf("Matrix:\n");
    for (int valRow = 0; valRow < dimRow; valRow++) {
        for (int valCol = 0; valCol < dimRow; valCol++) {
            printf("%d ", matrix[valRow][valCol]);
        }
        printf("\n");
    }

    int result = isMagicSquare(matrix, dimRow);
    if (result) {
        printf("M is a magic square (magic constant = %d)\n", result);
    } else {
        printf("M is NOT a magic square!\n");
    }

    for (int valRow = 0; valRow < dimRow; valRow++) {
        free(matrix[valRow]);
    }
    free(matrix);

    return 0;
}
