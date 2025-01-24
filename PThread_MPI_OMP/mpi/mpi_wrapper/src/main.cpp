#include<iostream>

#include "Mpi.hpp"
#include "MpiError.hpp"

int main(int argc, char* argv[]) {
    try {
        Mpi mpi(argc, argv);

        std::cout << "Hello from main thread of process " << mpi.getProcessNumber()
                  << " of " << mpi.getProcessCount() << " on " << mpi.getHostname()
                  << std::endl;

    } catch (const MpiError& error) {
        std::cerr << "MPI Error: " << error.what() << std::endl;
    }

    return 0;
}
