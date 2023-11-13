#ifndef MPI_HPP
#define MPI_HPP

#include <mpi.h>
#include <stdexcept>
#include <iostream>
#include <string>

class Mpi {
public:
    Mpi(int argc, char* argv[]) {
        // Inicializar el MPI.
        if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
            throw std::runtime_error("Error initializing MPI.");
        }

        // Obtener número de proceso.
        if (MPI_Comm_rank(MPI_COMM_WORLD, &process_number) != MPI_SUCCESS) {
            throw std::runtime_error("Error getting process number.");
        }

        // Obtener cantidad de procesos.
        if (MPI_Comm_size(MPI_COMM_WORLD, &process_count) != MPI_SUCCESS) {
            throw std::runtime_error("Error getting process count.");
        }

        // Obtener el nombre del host.
        char hostname[MPI_MAX_PROCESSOR_NAME];
        int hostname_length;
        if (MPI_Get_processor_name(hostname, &hostname_length) != MPI_SUCCESS) {
            throw std::runtime_error("Error getting hostname.");
        }
        process_hostname = std::string(hostname, hostname_length);
    }

    // Destructor.
    ~Mpi() {
        MPI_Finalize();
    }

    inline int getProcessNumber() const {
        return process_number;
    }

    inline int getProcessCount() const {
        return process_count;
    }

    inline const std::string& getHostname() const {
        return process_hostname;
    }

// Las variables pedidas.
private:
    int process_number;       // Número de proceso
    int process_count;        // Cantidad de procesos
    std::string process_hostname;  // Nombre del host
};

#endif // MPI_HPP