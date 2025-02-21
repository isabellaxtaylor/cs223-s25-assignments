/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 2/21/2025
 * Description: Writes pixel data to a PPM file in binary format.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "write_ppm.h"

// Writes a PPM file in binary format
void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s for writing\n", filename);
        return;
    }

    // Write the PPM header
    fprintf(fp, "P6\n%d %d\n255\n", w, h);

    // Write the pixel data
    if (fwrite(pxs, sizeof(struct ppm_pixel), w * h, fp) != (size_t)(w * h)) {
        fprintf(stderr, "Error: Failed to write pixel data\n");
    }

    fclose(fp);
}

