#include "../../mpi_wrapper/src/Mpi.hpp"
#include <cstdlib>
#include <ctime>

// Generate rand numbers, sum it with the one passed and then pass it to the next process.
int main(int argc, char* argv[]) {
  try {
    Mpi mpi(argc, argv);
    const int rank = mpi.getProcessNumber();
    const int count = mpi.getProcessCount();
    const int previous = (count + rank - 1) % count;
    const int next = (rank + 1) % count;

    std::srand(std::time(nullptr) + rank); // Numeros aleatorios.
    int random_number = std::rand() % 100; // (0-99).

    if (rank > 0) {
      int received_number;
      mpi.receive(received_number, previous);
      random_number = (random_number + received_number);
    }

    std::cout << "Random number from process " << rank << " before sum: " << random_number << std::endl;

    mpi.send(random_number, next);

    // Wait for the final result
    if (rank == 0) {
      int final_result;
      mpi.receive(final_result, previous);
      std::cout << "Final result: " << final_result << std::endl;
    }

  } catch (const std::exception& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  return 0;
}