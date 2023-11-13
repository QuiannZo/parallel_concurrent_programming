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

    // Metodos para enviar y recibir valores MPI de cualquier tipo.
    template <typename DataType>
    void send(const DataType& value, int toProcess, int tag = 0) const {
        MPI_Send(&value, 1, map(value), toProcess, tag, MPI_COMM_WORLD);
    }

    template <typename DataType>
    void receive(DataType& value, int fromProcess, int tag = MPI_ANY_TAG) const {
        MPI_Recv(&value, 1, map(value), fromProcess, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

private:
    int process_number;       // Número de proceso
    int process_count;        // Cantidad de procesos
    std::string process_hostname;  // Nombre del host

    // Mapeo de los tipos de datos a constantes MPI.
    template <typename DataType>
    static MPI_Datatype map(DataType) {
        if constexpr (std::is_same<DataType, bool>::value)
            return MPI_C_BOOL;
        else if constexpr (std::is_same<DataType, char>::value)
            return MPI_CHAR;
        else if constexpr (std::is_same<DataType, unsigned char>::value)
            return MPI_UNSIGNED_CHAR;
        else if constexpr (std::is_same<DataType, short>::value)
            return MPI_SHORT;
        else if constexpr (std::is_same<DataType, unsigned short>::value)
            return MPI_UNSIGNED_SHORT;
        else if constexpr (std::is_same<DataType, int>::value)
            return MPI_INT;
        else if constexpr (std::is_same<DataType, unsigned>::value)
            return MPI_UNSIGNED;
        else if constexpr (std::is_same<DataType, long>::value)
            return MPI_LONG;
        else if constexpr (std::is_same<DataType, unsigned long>::value)
            return MPI_UNSIGNED_LONG;
        else if constexpr (std::is_same<DataType, long long>::value)
            return MPI_LONG_LONG;
        else if constexpr (std::is_same<DataType, unsigned long long>::value)
            return MPI_UNSIGNED_LONG_LONG;
        else if constexpr (std::is_same<DataType, float>::value)
            return MPI_FLOAT;
        else if constexpr (std::is_same<DataType, double>::value)
            return MPI_DOUBLE;
        else if constexpr (std::is_same<DataType, long double>::value)
            return MPI_LONG_DOUBLE;
        else
            throw std::runtime_error("Unsupported MPI data type.");
    }
};

#endif // MPI_HPP