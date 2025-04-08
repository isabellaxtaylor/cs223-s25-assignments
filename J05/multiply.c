#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdlib.h> 

#define SIZE 100
#define NUM_THREADS 4

typedef struct {
    int start;            
    int end;              
    int *M;               
    int *u;               
    int *result_threads; 
} thread_data_t;

void *thread_mult(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    for (int i = data->start; i < data->end; i++) {
        int dot = 0;
        for (int j = 0; j < SIZE; j++) {
            dot += data->M[i * SIZE + j] * data->u[j];
        }
        data->result_threads[i] = dot;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    srand(time(0));

    int M[SIZE * SIZE];
    int u[SIZE];
    int result[SIZE];
    int result_threads[SIZE];

    for (int i = 0; i < SIZE; i++) {
        u[i] = rand() % 10 - 5;
        result[i] = 0;
        result_threads[i] = 0;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int value = rand() % 10 - 5;
            M[i * SIZE + j] = value;
            result[i] += value * u[j];
        }
    }

    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int block_size = SIZE / NUM_THREADS;

    for (int t = 0; t < NUM_THREADS; t++) {
        thread_data[t].start = t * block_size;
        thread_data[t].end = (t == NUM_THREADS - 1) ? SIZE : (t + 1) * block_size;
        thread_data[t].M = M;
        thread_data[t].u = u;
        thread_data[t].result_threads = result_threads;
        
        int rc = pthread_create(&threads[t], NULL, thread_mult, (void *)&thread_data[t]);
    }

    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    int error = 0;
    for (int i = 0; i < SIZE; i++) {
        error += abs(result[i] - result_threads[i]);
    }
    printf("Error between ground truth and multithreaded version: %d\n", error);

    return 0;
}
