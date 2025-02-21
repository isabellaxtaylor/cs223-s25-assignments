/*----------------------------------------------
 * Author: Isabella taylor
 * Date: 2/21/2025
 * Description: Reads and prints pixel data from a PPM file.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
    int w, h;

    // Read the PPM file
    struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &w, &h);
    if (!pixels) {
        fprintf(stderr, "Error: Failed to read PPM file\n");
        return 1;
    }

    // Print the width and height
    printf("Testing file feep-raw.ppm: %d %d\n", w, h);

    // Print the pixel values
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            struct ppm_pixel pixel = pixels[i * w + j];
            printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }

    free(pixels);
    return 0;
}


