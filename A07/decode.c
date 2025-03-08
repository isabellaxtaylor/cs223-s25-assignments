/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 3/7/2025
 * Description: PPM file message decoder.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <ppm_file>\n", argv[0]);
        return 1;
    }

    int width, height;
    struct ppm_pixel* pixels = read_ppm(argv[1], &width, &height);
    if (!pixels) {
        fprintf(stderr, "Error: Could not read PPM file.\n");
        return 1;
    }

    int max_chars = (width * height * 3) / 8;
    printf("Reading %s with width %d and height %d\n", argv[1], width, height);
    printf("Max number of characters in the image: %d\n", max_chars);

    unsigned char* message = malloc(max_chars + 1);
    if (!message) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        free(pixels);
        return 1;
    }

    int bit_index = 0;
    unsigned char current_char = 0;
    int char_count = 0;
    int total_pixels = width * height;

    for (int i = 0; i < total_pixels * 3; i++) { 
        unsigned char color_component;
        
        if (i % 3 == 0) {
            color_component = pixels[i / 3].red;
        } else if (i % 3 == 1) {
            color_component = pixels[i / 3].green;
        } else {
            color_component = pixels[i / 3].blue;
        }

        current_char |= (color_component & 1) << (7 - (bit_index % 8));
        bit_index++;

        if (bit_index % 8 == 0) {
            message[char_count] = current_char;
            if (current_char == '\0') break;
            char_count++;
            current_char = 0;
        }
    }

    message[char_count] = '\0';
    printf("%s\n", message);

    free(message);
    free(pixels);
    return 0;
}
