#ifndef MPI_HPP
#define MPI_HPP

#include <mpi.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

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

    // Send a scalar value to another process
    template <typename Type>
    void send(const Type& value, int toProcess, int tag = 0) const {
        MPI_Send(&value, 1, map(value), toProcess, tag, MPI_COMM_WORLD);
    }

    // Send an array of count values to another process
    template <typename Type>
    void send(const Type* values, int count, int toProcess, int tag = 0) const {
        MPI_Send(values, count, map(values[0]), toProcess, tag, MPI_COMM_WORLD);
    }

    // Send an array of values to another process
    template <typename Type>
    void send(const std::vector<Type>& values, int toProcess, int tag = 0) const {
        MPI_Send(values.data(), values.size(), map(values[0]), toProcess, tag, MPI_COMM_WORLD);
    }

    // Send a text to another process
    void send(const std::string& text, int toProcess, int tag = 0) const {
        const char* c_str = text.c_str();
        MPI_Send(c_str, text.size() + 1, MPI_CHAR, toProcess, tag, MPI_COMM_WORLD);
    }

    // Wait until it receives a scalar value from another process
    template <typename Type>
    void receive(Type& value, int fromProcess = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG) const {
        MPI_Recv(&value, 1, map(value), fromProcess, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Wait until it receives at most capacity values from another process
    template <typename Type>
    void receive(Type* values, int capacity, int fromProcess = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG) const {
        MPI_Recv(values, capacity, map(values[0]), fromProcess, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Wait until it receives at most capacity values from another process
    template <typename Type>
    void receive(std::vector<Type>& values, int capacity, int fromProcess = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG) const {
        values.resize(capacity);
        MPI_Recv(values.data(), capacity, map(values[0]), fromProcess, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Wait until it receives a text of at most length chars from another process
    void receive(std::string& text, int capacity, int fromProcess = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG) const {
        char buffer[capacity + 1];
        buffer[capacity + 1] = '\0';
        MPI_Recv(buffer, capacity, MPI_CHAR, fromProcess, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        text = buffer;
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

    // Mapeo para tipo array.
    template <typename Type>
    static MPI_Datatype map(const std::vector<Type>&) {
        return map(Type());
    }
};

#endif // MPI_HPP