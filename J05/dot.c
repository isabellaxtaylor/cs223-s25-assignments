#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000
#define NUM_THREADS 4

typedef struct {
    int start;          
    int end;            
    int *u;             
    int *v;             
    long partial_sum;   
} thread_data_t;

void *compute_dot_product(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    long sum = 0;
    for (int i = data->start; i < data->end; i++) {
         sum += (long)data->u[i] * data->v[i];
    }
    data->partial_sum = sum;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    srand(time(0));

    int v[SIZE];
    int u[SIZE];
    int dotproduct = 0;

    for (int i = 0; i < SIZE; i++) {
        v[i] = rand() % 1000 - 500;
        u[i] = rand() % 1000 - 500;
        dotproduct += u[i] * v[i];
    }
    printf("Ground truth dot product: %d\n", dotproduct);

    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int block_size = SIZE / NUM_THREADS;
    
    for (int t = 0; t < NUM_THREADS; t++) {
        thread_data[t].start = t * block_size;
        thread_data[t].end = (t == NUM_THREADS - 1) ? SIZE : (t + 1) * block_size;
        thread_data[t].u = u;
        thread_data[t].v = v;
        thread_data[t].partial_sum = 0;
        
        int rc = pthread_create(&threads[t], NULL, compute_dot_product, (void *)&thread_data[t]);
    }

    long thread_dotproduct = 0;
    for (int t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
        thread_dotproduct += thread_data[t].partial_sum;
    }
    
    printf("Answer with threads: %ld\n", thread_dotproduct);

    return 0;
}
