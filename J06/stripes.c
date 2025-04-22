#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "write_ppm.h"

#define SIZE 1024

struct thread_data {
    int starti;
    int endi;
    int width;
    int height;
    struct ppm_pixel color;
    struct ppm_pixel *image;
};

void *start(void *userdata) {
    struct thread_data *d = userdata;
    printf("Thread is coloring rows %d to %d with color: %d %d %d\n",
           d->starti, d->endi,
           d->color.red, d->color.green, d->color.blue);

    for (int row = d->starti; row <= d->endi; row++) {
        for (int col = 0; col < d->width; col++) {
            d->image[row * d->width + col] = d->color;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <num_of_stripes>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int N = strtol(argv[1], NULL, 10);

    struct ppm_pixel *image = malloc(SIZE * SIZE * sizeof *image);
    pthread_t *threads = malloc(N * sizeof *threads);
    struct thread_data *td = malloc(N * sizeof *td);

    if (!image || !threads || !td) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    srand((unsigned)time(NULL));

    int base = SIZE / N;
    int rem = SIZE % N;
    int cur = 0;

    for (int i = 0; i < N; i++) {
        int h = base + (i < rem ? 1 : 0);

        td[i].starti = cur;
        td[i].endi = cur + h - 1;
        td[i].width = SIZE;
        td[i].height = SIZE;
        td[i].image = image;

        td[i].color.red = rand() % 256;
        td[i].color.green = rand() % 256;
        td[i].color.blue = rand() % 256;

        cur += h;
        if (pthread_create(&threads[i], NULL, start, &td[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    write_ppm("stripes.ppm", image, SIZE, SIZE);

    free(image);
    free(threads);
    free(td);
    return 0;
}
