/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 2/21/2025
 * Description: Reads a PPM file, prints pixel values, and writes to a new file.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main() {
    int width, height;
    
    // Read the original PPM file
    struct ppm_pixel* pixels = read_ppm("feep-raw.ppm", &width, &height);
    if (!pixels) {
        fprintf(stderr, "Error: Failed to read PPM file\n");
        return 1;
    }

    printf("Testing file feep-raw.ppm: %d %d\n", width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            struct ppm_pixel pixel = pixels[i * width + j];
            printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }

    // Write the file to a new test PPM
    write_ppm("test.ppm", pixels, width, height);

    // Read the newly written PPM file
    struct ppm_pixel* test_pixels = read_ppm("test.ppm", &width, &height);
    if (!test_pixels) {
        fprintf(stderr, "Error: Failed to read test PPM file\n");
        free(pixels);
        return 1;
    }

    printf("\nVerifying test.ppm contents:\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            struct ppm_pixel pixel = test_pixels[i * width + j];
            printf("(%d,%d,%d) ", pixel.red, pixel.green, pixel.blue);
        }
        printf("\n");
    }

    free(pixels);
    free(test_pixels);
    return 0;
}
