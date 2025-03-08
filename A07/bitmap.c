/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 3/7/2025
 * Description: Converts 64-bit hex to 8x8 bitmap.
 ---------------------------------------------*/
#include <stdio.h>

int main() {
    unsigned long img;
    scanf(" %lx", &img);
    printf("Image (unsigned long): %lx\n", img);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            unsigned long mask = 0x1ul << (63 - (i * 8 + j));

            if (img & mask) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
