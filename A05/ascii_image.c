/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 2/21/2025
 * Description: Converts a PPM image to ASCII art based on pixel intensity.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

// Function to map intensity to an ASCII character
char intensity_to_ascii(int intensity) {
    if (intensity >= 0 && intensity <= 25) return '@';
    if (intensity >= 26 && intensity <= 50) return '#';
    if (intensity >= 51 && intensity <= 75) return '%';
    if (intensity >= 76 && intensity <= 100) return '*';
    if (intensity >= 101 && intensity <= 125) return 'o';
    if (intensity >= 126 && intensity <= 150) return ';';
    if (intensity >= 151 && intensity <= 175) return ':';
    if (intensity >= 176 && intensity <= 200) return ',';
    if (intensity >= 201 && intensity <= 225) return '.';
    if (intensity >= 226 && intensity <= 255) return ' ';
    return ' ';
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    // Read the PPM file
    int width, height;
    struct ppm_pixel* pixels = read_ppm(argv[1], &width, &height);
    if (!pixels) {
        fprintf(stderr, "Error: Failed to read PPM file %s\n", argv[1]);
        return 1;
    }

    printf("Reading %s with width %d and height %d\n", argv[1], width, height);

    // Process the image and print ASCII Art
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            struct ppm_pixel pixel = pixels[i * width + j];
            int intensity = (pixel.red + pixel.green + pixel.blue) / 3; // Calculate average intensity
            char ascii_char = intensity_to_ascii(intensity);  // Map intensity to ASCII character
            printf("%c", ascii_char);
        }
        printf("\n");
    }

    free(pixels);
    return 0;
}
