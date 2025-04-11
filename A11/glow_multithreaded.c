/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 04/11/2025
 * Description: Multithreaded image glow processor
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "read_ppm.h"
#include "write_ppm.h"

struct thread_args {
    struct ppm_pixel* original;
    struct ppm_pixel* bright;
    struct ppm_pixel* blur;
    int width;
    int height;
    int start_row;
    int end_row;
    int threshold;
    int blur_size;
};

int clamp(int val, int min, int max) {
    return val < min ? min : (val > max ? max : val);
}

void* process_slice(void* args_ptr) {
    struct thread_args* args = (struct thread_args*)args_ptr;
    int width = args->width;
    int height = args->height;
    int blur_size = args->blur_size;
    int radius = blur_size / 2;

    for (int y = args->start_row; y < args->end_row; y++) {
        for (int x = 0; x < width; x++) {
            int i = y * width + x;
            int brightness = (args->original[i].red + args->original[i].green + args->original[i].blue) / 3;
            if (brightness >= args->threshold) {
                args->bright[i] = args->original[i];
            } else {
                args->bright[i].red = 0;
                args->bright[i].green = 0;
                args->bright[i].blue = 0;
            }
        }
    }

    for (int y = args->start_row; y < args->end_row; y++) {
        for (int x = 0; x < width; x++) {
            int r_sum = 0, g_sum = 0, b_sum = 0, count = 0;
            for (int dy = -radius; dy <= radius; dy++) {
                for (int dx = -radius; dx <= radius; dx++) {
                    int nx = clamp(x + dx, 0, width - 1);
                    int ny = clamp(y + dy, 0, height - 1);
                    int idx = ny * width + nx;
                    r_sum += args->bright[idx].red;
                    g_sum += args->bright[idx].green;
                    b_sum += args->bright[idx].blue;
                    count++;
                }
            }
            int i = y * width + x;
            args->blur[i].red   = r_sum / count;
            args->blur[i].green = g_sum / count;
            args->blur[i].blue  = b_sum / count;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) 
{
  int num_threads = 4;
  int threshold = 200;
  int blur_size = 24;
  const char* filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1) {
    switch (opt) {
      case 'N': num_threads = atoi(optarg); break;
      case 't': threshold = atoi(optarg); break;
      case 'b': blur_size = atoi(optarg); break;
      case 'f': filename = optarg; break;
      case '?':
        printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]);
        return 1;
    }
  }

  int width, height;
  struct ppm_pixel* original = read_ppm(filename, &width, &height);
  if (!original) {
    fprintf(stderr, "Error loading image.\n");
    return 1;
  }

  int size = width * height;
  struct ppm_pixel* bright = calloc(size, sizeof(struct ppm_pixel));
  struct ppm_pixel* blur = calloc(size, sizeof(struct ppm_pixel));
  struct ppm_pixel* output = malloc(sizeof(struct ppm_pixel) * size);

  pthread_t* threads = malloc(sizeof(pthread_t) * num_threads);
  struct thread_args* args = malloc(sizeof(struct thread_args) * num_threads);

  int slice_height = height / num_threads;

  for (int i = 0; i < num_threads; i++) {
    args[i].original = original;
    args[i].bright = bright;
    args[i].blur = blur;
    args[i].width = width;
    args[i].height = height;
    args[i].start_row = i * slice_height;
    args[i].end_row = (i + 1) * slice_height;
    args[i].threshold = threshold;
    args[i].blur_size = blur_size;

    printf("Thread sub-image slice: rows (%d,%d)\n", args[i].start_row, args[i].end_row);
    pthread_create(&threads[i], NULL, process_slice, &args[i]);
  }

  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  for (int i = 0; i < size; i++) {
    int r = original[i].red + blur[i].red;
    int g = original[i].green + blur[i].green;
    int b = original[i].blue + blur[i].blue;
    output[i].red = clamp(r, 0, 255);
    output[i].green = clamp(g, 0, 255);
    output[i].blue = clamp(b, 0, 255);
  }

  write_ppm("glow.ppm", output, width, height);

  free(original);
  free(bright);
  free(blur);
  free(output);
  free(threads);
  free(args);

  return 0;
}
