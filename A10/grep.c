/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 04/05/2025
 * Description: Multithreaded keyword file search
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    int thread_id;
    int start_idx;
    int end_idx;
    char **files;
    int num_files;
    char *keyword;
    int local_count;  
} thread_data_t;

static int total_count = 0;
static pthread_mutex_t lock;

void *search_files(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    data->local_count = 0;

    if (data->start_idx > data->end_idx) {
        pthread_exit(NULL);
    }

    int num_files_for_thread = data->end_idx - data->start_idx + 1;
    printf("Thread %d scans %d files (%d to %d)\n",
           data->thread_id,
           num_files_for_thread,
           data->start_idx,
           data->end_idx);

    for (int i = data->start_idx; i <= data->end_idx; i++) {
        FILE *fp = fopen(data->files[i], "r");
        if (!fp) {
            continue;
        }
        char line[1024];
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, data->keyword) != NULL) {
                data->local_count++;
                printf("  %s:%s", data->files[i], line);
            }
        }
        fclose(fp);
    }

    pthread_mutex_lock(&lock);
    total_count += data->local_count;
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "usage: %s <NumThreads> <Keyword> <Files>\n", argv[0]);
        fprintf(stderr, "thread grep\n");
        return EXIT_FAILURE;
    }

    int num_threads = atoi(argv[1]);
    char *keyword = argv[2];
    int num_files = argc - 3;
    char **files = &argv[3];

    if (num_threads <= 0) {
        fprintf(stderr, "Error: number of threads must be positive.\n");
        return EXIT_FAILURE;
    }

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    if (threads == NULL) {
        perror("malloc threads");
        exit(EXIT_FAILURE);
    }
    thread_data_t *thread_data = malloc(num_threads * sizeof(thread_data_t));
    if (thread_data == NULL) {
        perror("malloc thread_data");
        free(threads);
        exit(EXIT_FAILURE);
    }

    pthread_mutex_init(&lock, NULL);

    int files_per_thread = num_files / num_threads;
    int remainder = num_files % num_threads;
    int start_idx = 0;
    int i;
    for (i = 0; i < num_threads; i++) {
        int end_idx = start_idx + files_per_thread - 1;
        if (remainder > 0) {
            end_idx++;
            remainder--;
        }
        if (end_idx >= num_files) {
            end_idx = num_files - 1;
        }

        thread_data[i].thread_id = i + 1;
        thread_data[i].start_idx = start_idx;
        thread_data[i].end_idx = (start_idx <= end_idx) ? end_idx : start_idx - 1;
        thread_data[i].files = files;
        thread_data[i].num_files = num_files;
        thread_data[i].keyword = keyword;
        thread_data[i].local_count = 0;

        pthread_create(&threads[i], NULL, search_files, &thread_data[i]);

        start_idx = end_idx + 1;
        if (start_idx >= num_files) {
            break;
        }
    }

    for (int j = 0; j < i; j++) {
        pthread_join(threads[j], NULL);
    }

    pthread_mutex_destroy(&lock);
    free(threads);
    free(thread_data);

    printf("Found %d lines containing keyword: %s\n", total_count, keyword);
    return EXIT_SUCCESS;
}
