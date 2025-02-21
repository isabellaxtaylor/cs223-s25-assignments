/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 2/21/2025
 * Description: Applies a glitch effect to an image by bit-shifting colors.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "read_ppm.h"
#include "write_ppm.h"

void apply_glitch(struct ppm_pixel* pxs, int w, int h) {
    for (int i = 0; i < w * h; i++) {
        struct ppm_pixel* pixel = &pxs[i];
        
        // Apply a random bit shift (either 1 or 2)
        pixel->red   = pixel->red   << (rand() % 2);
        pixel->green = pixel->green << (rand() % 2);
        pixel->blue  = pixel->blue  << (rand() % 2);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    // Read the original PPM file
    int width, height;
    struct ppm_pixel* pixels = read_ppm(argv[1], &width, &height);
    if (!pixels) {
        fprintf(stderr, "Error: Failed to read PPM file %s\n", argv[1]);
        return 1;
    }

    printf("Reading %s with width %d and height %d\n", argv[1], width, height);

    apply_glitch(pixels, width, height);

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s-glitch.ppm", argv[1]);

    // Write the glitched image to a new file
    write_ppm(output_filename, pixels, width, height);
    printf("Writing file %s\n", output_filename);

    free(pixels);
    return 0;
}
