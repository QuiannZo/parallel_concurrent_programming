#include "../../mpi_wrapper/src/Mpi.hpp"
#include "../../mpi_wrapper/src/MpiError.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


const size_t MESSAGE_CAPACITY = 512;

void greet(const Mpi& mpi);

int main(int argc, char* argv[]) {
    try {
        Mpi mpi(argc, argv);
        greet(mpi);
    } catch (const std::runtime_error& exception) {
        std::cerr << "error: " << exception.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void greet(const Mpi& mpi) {
    int process_number = mpi.getProcessNumber();
    int process_count = mpi.getProcessCount();
    const std::string& process_hostname = mpi.getHostname();

    std::stringstream buffer;
    buffer << "Hello from main thread of process " << process_number
           << " of " << process_count << " on " << process_hostname;

    if (process_number != 0) {
        const std::string& message = buffer.str();
        mpi.send(message, 0, 0);
    } else {
        std::cout << process_number << " said " << buffer.str() << std::endl;
        for (int source = 1; source < process_count; ++source) {
            std::string message;
            mpi.receive(message, MESSAGE_CAPACITY, source, 0);
            std::cout << source << " sent " << message << std::endl;
        }
    }
}