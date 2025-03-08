/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 3/7/2025
 * Description: PPM file message encoder.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"
#include "write_ppm.h"

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

    char* message = (char*)malloc((max_chars + 1) * sizeof(char));
    if (!message) {
        fprintf(stderr, "Error: Memory allocation failed for message\n");
        free(pixels);
        return 1;
    }

    printf("Enter a phrase: ");
    fgets(message, max_chars + 1, stdin);
    
    message[strcspn(message, "\n")] = '\0';

    int msg_length = strlen(message) + 1; 
    if (msg_length > max_chars) {
        fprintf(stderr, "Error: Message is too long! Max allowed: %d characters\n", max_chars);
        free(message);
        free(pixels);
        return 1;
    }

    int bit_index = 0;
    for (int i = 0; i < msg_length; i++) { 
        for (int bit = 0; bit < 8; bit++) { 
            int pixel_index = bit_index / 3;
            int color_component = bit_index % 3;
            unsigned char bit_value = (message[i] >> (7 - bit)) & 1; 

            if (color_component == 0) {
                pixels[pixel_index].red = (pixels[pixel_index].red & 0xFE) | bit_value;
            } else if (color_component == 1) {
                pixels[pixel_index].green = (pixels[pixel_index].green & 0xFE) | bit_value;
            } else {
                pixels[pixel_index].blue = (pixels[pixel_index].blue & 0xFE) | bit_value;
            }

            bit_index++;
        }
    }

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s-encoded.ppm", argv[1]);

    printf("Writing file %s\n", output_filename);
    write_ppm(output_filename, pixels, width, height);

    free(message);
    free(pixels);
    return 0;
}
