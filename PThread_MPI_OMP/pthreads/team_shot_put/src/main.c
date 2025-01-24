#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// El hilo principal es el arbitro. El hilo principal obtiene la cantidad de atletas por argumento de línea de comandos.
// Seguidamente crea dos equipos de la misma cantidad de atletas (hlios secundarios).

// Cada atleta lanza la bala tres veces, lo cual se puede simular generando tres números pseudoaleatorios, 
// tomar el mayor de ellos, imprimirlo en la salida estándar, y reportarlo al árbitro como su valor de retorno.

// Main thread mfunction.
void* get_data(void* data);

// First athlete data generation.
void* shot_one(void* data);

// Second athlete data generation.
void* shot_two(void* data);

int main(void){
  // create_thread. (The main thread).
  pthread_t thread;
  int error = pthread_create(&thread, /*attr*/ NULL, get_data, /*arg*/ NULL);
  if (error == EXIT_SUCCESS) {
    // Join thread.
    pthread_join(thread, /*value_ptr*/ NULL);
  } else {
    fprintf(stderr, "Error: could not create main thread\n");
  }
  return error;
}

void* get_data(void* data){
    // Get an odd number.
    int players_per_team;
    scanf("%d", &players_per_team);
    if(players_per_team % 2 == 0) {
        fprintf(stderr, "Error: the number must be odd.\n");
        // Return an error if not odd.
        return 1;
    }

    // Create secundary threads.

    // Cada atleta lanza la bala tres veces, lo cual se puede simular generando tres números pseudoaleatorios,
    // tomar el mayor de ellos, imprimirlo en la salida estándar, y reportarlo al árbitro como su valor de retorno.

    for(int i = 0; i < players_per_team; ++i){
        // create_thread athlete_one.
        pthread_t thread_one;
        double num_one;
        int error_one = pthread_create(&thread_one, NULL, shot_one, &num_one);
        if (error_one == EXIT_SUCCESS) {
            pthread_join(thread_one, &num_one);
            printf("1.%d : best shot_put %lfm", players_per_team, (double)num_one);
        } else {
            fprintf(stderr, "Error: could not create secondary thread\n");
            return 1;
        }

        // create_thread athlete_two.
        pthread_t thread_two;
        double num_two;
        int error_two = pthread_create(&thread_two, /*attr*/ NULL, shot_two, /*arg*/ &num_two);
        if (error_two == EXIT_SUCCESS) {
            pthread_join(thread_two, &num_two);
        } else {
            fprintf(stderr, "Error: could not create secondary thread\n");
            return 1;
        }
    }

    return 0;
}

// First athlete data generation.
void* shot_one(void* data){
    (double)data;

    srand(time(NULL)); // init.
    // generate a random num from 0 to 25.0
    data = (rand() % 250) / 10;

    return data;
}

// Second athlete data generation.
void* shot_two(void* data){
    (double)data;

    srand(time(NULL)); // init.
    // generate a random num from 0 to 25.0
    data = (rand() % 250) / 10;

    return data;
}