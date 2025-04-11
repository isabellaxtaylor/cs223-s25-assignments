/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 04/11/2025
 * Description: Single-threaded image glow filter
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read_ppm.h"
#include "write_ppm.h"

int clamp(int x, int low, int high) {
    if(x < low)  return low;
    if(x > high) return high;
    return x;
}

int main(int argc, char* argv[]) {
    int width, height;

    struct ppm_pixel* original = read_ppm("earth-small.ppm", &width, &height);
    if(!original) {
        fprintf(stderr, "Error reading input image.\n");
        return 1;
    }

    int size = width * height;

    struct ppm_pixel* bright = malloc(sizeof(struct ppm_pixel) * size);
    struct ppm_pixel* blur   = malloc(sizeof(struct ppm_pixel) * size);
    struct ppm_pixel* glow   = malloc(sizeof(struct ppm_pixel) * size);
    if(!bright || !blur || !glow) {
        fprintf(stderr, "Memory allocation error.\n");
        return 1;
    }

    int threshold = 200; 
    for (int i = 0; i < size; i++) {
        int r = original[i].red;
        int g = original[i].green;
        int b = original[i].blue;
        int brightness = (r + g + b) / 3;
        if (brightness >= threshold) {
            bright[i].red   = r;
            bright[i].green = g;
            bright[i].blue  = b;
        } else {
            bright[i].red   = 0;
            bright[i].green = 0;
            bright[i].blue  = 0;
        }
    }


    int radius = 2;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int r_sum = 0, g_sum = 0, b_sum = 0, count = 0;
            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        int idx = ny * width + nx;
                        r_sum += bright[idx].red;
                        g_sum += bright[idx].green;
                        b_sum += bright[idx].blue;
                        count++;
                    }
                }
            }
            int idx = y * width + x;
            blur[idx].red   = r_sum / count;
            blur[idx].green = g_sum / count;
            blur[idx].blue  = b_sum / count;
        }
    }

    for (int i = 0; i < size; i++) {
        int r = original[i].red   + blur[i].red;
        int g = original[i].green + blur[i].green;
        int b = original[i].blue  + blur[i].blue;
        glow[i].red   = clamp(r, 0, 255);
        glow[i].green = clamp(g, 0, 255);
        glow[i].blue  = clamp(b, 0, 255);
    }

    write_ppm("glow.ppm", glow, width, height);

    free(original);
    free(bright);
    free(blur);
    free(glow);
  printf("Glow effect applied. Output saved as glow.ppm\n");

    return 0;
}
