// Copyright 2021 Jeisson Hidalgo <jeisson.hidalgo@ucr.ac.cr> CC-BY 4.0

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

/**
 * @brief recursive function for salute
 * @param data the number to use in the func.
 */
void* greet(void* data);

// procedure main:
int main(void) {
  // size_t var. init to 2.
  size_t num = 2;
  // create_thread(greet)
  pthread_t thread;
  int error = pthread_create(&thread, /*attr*/ NULL, greet, /*arg*/ num);
  if (error == EXIT_SUCCESS) {
    // print "Hello from main thread"
    // usleep(1);  // indeterminism
    pthread_join(thread, /*value_ptr*/ NULL);
  } else {
    fprintf(stderr, "Error: could not create secondary thread\n");
  }
  return error;
}  // end procedure

// procedure greet:
void* greet(void* data) {
  // cast data.
  (size_t)data;
  // print "Hello from secondary thread"
  if(data == 0){
    printf("Good bye. %d\n", data);
  } else if (data > 0){
    printf("Hello. %d\n", data);
    pthread_t thread;
    int error = pthread_create(&thread, /*attr*/ NULL, greet, /*arg*/ --data);
    if (error == EXIT_SUCCESS) {
        pthread_join(thread, /*value_ptr*/ NULL);
        } else {
        fprintf(stderr, "Error: could not create secondary thread\n");
    }
    return error;
  }
  return NULL;
}  // end procedure