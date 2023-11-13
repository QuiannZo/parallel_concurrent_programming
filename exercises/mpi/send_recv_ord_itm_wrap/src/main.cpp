#include "../../mpi_wrapper/src/Mpi.hpp"
#include "../../mpi_wrapper/src/MpiError.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    try {
        Mpi mpi(argc, argv);
        int rank = mpi.getProcessNumber();
        int size = mpi.getProcessCount();
        int intermediary = (rank + 1) % size;

        if (rank == 0) {
            // Process 0 sends text to the intermediary
            std::string text = "Hello from process 0!";
            mpi.send(text, intermediary);
        }

        // All processes (including the intermediary) receive the text
        std::string receivedText;
        mpi.receive(receivedText, intermediary);

        // All processes (including the intermediary) send the received text to the next process
        mpi.send(receivedText, (rank + 1) % size);

        // Process 0 receives the final text from the last process
        if (rank == 0) {
            std::string finalText;
            mpi.receive(finalText, size - 1);
            std::cout << finalText << std::endl;
        }
    } catch (const MpiError& error) {
        std::cerr << "MPI Error: " << error.what() << std::endl;
    }

    return 0;
}
