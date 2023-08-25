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
// func to generate the numbers.
void* gennum(void* data);

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

void* gennum_dir(void* data){
  srand(time(NULL)); // init.
  // generate a random num from 0 to 99.
  int r = rand() % 100;
  return &r;
}

void* gennum_fdir(void* data){
  srand(time(NULL)); // init.
  // generate a random num from 0 to 99.
  int r = rand() % 100;
  return &r;
}

void* generate(void* data){
  // create_thread one(gennum)
  pthread_t thread_one;
  void* num_one;
  int error_one = pthread_create(&thread_one, /*attr*/ NULL, gennum_dir, /*arg*/ NULL);
  if (error_one == EXIT_SUCCESS) {
    pthread_join(thread_one, /*value_ptr*/ NULL);
    return 0;
  } else {
    fprintf(stderr, "Error: could not create secondary thread\n");
  }

  // create_thread two(gennum)
  pthread_t thread_two;
  int error_two = pthread_create(&thread_two, /*attr*/ NULL, gennum_fdir, /*arg*/ NULL);
  if (error_two == EXIT_SUCCESS) {
    pthread_join(thread_two, /*value_ptr*/ NULL);
    return 0;
  } else {
    fprintf(stderr, "Error: could not create secondary thread\n");
  }

  return 1;
}