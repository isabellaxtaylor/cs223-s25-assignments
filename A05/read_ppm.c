/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 2/21/2025
 * Description: Reads a PPM file, extracts pixel data, and returns it.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }

    // Read and check the magic number
    char magic[3];
    if (!fgets(magic, sizeof(magic), fp) || strncmp(magic, "P6", 2) != 0) {
        fprintf(stderr, "Error: Not a valid P6 PPM file\n");
        fclose(fp);
        return NULL;
    }

    // Skip comments and read width and height
    char line[128];
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '#') continue;
        if (sscanf(line, "%d %d", w, h) == 2) {
            break;
        }
    }

    if (*w <= 0 || *h <= 0) {
        fprintf(stderr, "Error: Invalid PPM width/height\n");
        fclose(fp);
        return NULL;
    }

    // Read max color value
    int maxval;
    if (fscanf(fp, "%d", &maxval) != 1 || maxval != 255) {
        fprintf(stderr, "Error: Unsupported max color value\n");
        fclose(fp);
        return NULL;
    }
    fgetc(fp);

    // Allocate memory for pixel data
    struct ppm_pixel* pixels = malloc((*w) * (*h) * sizeof(struct ppm_pixel));
    if (!pixels) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }

    // Read pixel data
    if (fread(pixels, sizeof(struct ppm_pixel), (*w) * (*h), fp) != (size_t)(*w) * (*h)) {
        fprintf(stderr, "Error: Failed to read pixel data\n");
        free(pixels);
        fclose(fp);
        return NULL;
    }

    fclose(fp);
    return pixels;
}


