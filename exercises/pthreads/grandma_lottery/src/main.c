#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* llama a la abuela como el hilo principal.
* la abuela llama dos hilos paralelos que son los nietos.
* los nietos hacen sus procesos y luego hacen join con la abuela.
*/

// func to generate two threads with random num generators.
void* generate(void* data);
// func to generate nums.
void* gennum(void* data);

srand(time(NULL)); // initialization. called once.

// main func.
int main(void) {
  // create_thread(generate)
  pthread_t thread;
  int error = pthread_create(&thread, /*attr*/ NULL, generate, /*arg*/ NULL);
  if (error == EXIT_SUCCESS) {
    // Join thread.
    pthread_join(thread, /*value_ptr*/ NULL);
  } else {
    fprintf(stderr, "Error: could not create secondary thread\n");
  }
  return error;
}

void* gennum(void* data){
  // generate a random num from 0 to 99.
  int r = rand(0, 100);
}

void* generate(void* data){
  // create_thread one(gennum)
  pthread_t thread_one;
  int error = pthread_create(&thread_one, /*attr*/ NULL, gennum, /*arg*/ NULL);
  if (error == EXIT_SUCCESS) {
    pthread_join(thread_one, /*value_ptr*/ NULL);
  } else {
    fprintf(stderr, "Error: could not create secondary thread\n");
  }
  return error;
}