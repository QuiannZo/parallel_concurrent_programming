#include <iostream>
#include "../../mpi_wrapper/src/Mpi.hpp"
#include "../../mpi_wrapper/src/MpiError.hpp"

int main(int argc, char* argv[]) {
    Mpi mpi(argc, argv);

    if (mpi.getProcessNumber() > 0) {
        MpiStream stream = mpi[0];
        stream << "Hello from " << mpi.getProcessNumber();

    } else {
        for (int source = 1; source < mpi.getProcessCount(); ++source) {
            std::string text;
            int rank;

            MpiStream stream = mpi[source];
            stream >> text >> rank;

            std::cout << source << " says: " << text << rank << std::endl;
        }
    }

    return 0;
}