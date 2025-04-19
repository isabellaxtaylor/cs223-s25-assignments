/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 04/18/2025
 * Description: Single‑lane bridge synchronization
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>

typedef enum { OUTLOOK, TOWN } location_t;
const char* location_string[2] = { "Outlook", "Town" };

struct bridge_t {
  int num_on_bridge[2];       
  pthread_mutex_t lock;
  pthread_cond_t  free;      
} bridge; 

struct thread_data {
  int id;
  int num_trips;
  location_t start_destination;
};

void *Move(void *args){
  struct thread_data* data = (struct thread_data*) args;
  int id = data->id;
  location_t destination = data->start_destination;

  for (int i = 0; i < data->num_trips; i++) {
    pthread_mutex_lock(&bridge.lock);
    while (bridge.num_on_bridge[(destination+1)%2] > 0) {
      pthread_cond_wait(&bridge.free, &bridge.lock);
    }
    bridge.num_on_bridge[destination]++;
    assert(bridge.num_on_bridge[(destination+1)%2] == 0);
    pthread_mutex_unlock(&bridge.lock);

    printf("Tourist %d takes their %d/%d trip towards %s\n",
           id, i, data->num_trips, location_string[destination]);
    sleep(rand() / (double)RAND_MAX);

    pthread_mutex_lock(&bridge.lock);
    bridge.num_on_bridge[destination]--;
    assert(bridge.num_on_bridge[destination] >= 0);
    assert(bridge.num_on_bridge[(destination+1)%2] == 0);
    if (bridge.num_on_bridge[destination] == 0) {
      pthread_cond_broadcast(&bridge.free);
    }
    pthread_mutex_unlock(&bridge.lock);

    sleep(rand() / (double)RAND_MAX);
    destination = (destination + 1) % 2;
  }

  return NULL;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "usage: %s <NumThreads> <NumTrips>\n", argv[0]);
    exit(1);
  }

  int N      = strtol(argv[1], NULL, 10);
  int ntrips = strtol(argv[2], NULL, 10);

  bridge.num_on_bridge[OUTLOOK] = bridge.num_on_bridge[TOWN] = 0;
  pthread_mutex_init(&bridge.lock, NULL);
  pthread_cond_init(&bridge.free, NULL);

  pthread_t* threads = malloc(sizeof(*threads) * N);
  struct thread_data* data = malloc(sizeof(*data) * N);
  for (int i = 0; i < N; i++) {
    data[i].id = i;
    data[i].num_trips = ntrips;
    data[i].start_destination = (i < (N+1)/2 ? OUTLOOK : TOWN);
    pthread_create(&threads[i], NULL, Move, &data[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  free(threads);
  free(data);
  pthread_mutex_destroy(&bridge.lock);
  pthread_cond_destroy(&bridge.free);
  return 0;
}


