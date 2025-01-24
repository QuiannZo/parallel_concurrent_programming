#include "Mpi.hpp"
#include "MpiError.hpp"

MpiError::MpiError(const std::string& message)
    : std::runtime_error(message) {}

MpiError::MpiError(const std::string& message, const Mpi& mpi)
    : std::runtime_error(mpi.getHostname() + ":" + std::to_string(mpi.getProcessNumber()) + ": " + message) {}

MpiError::MpiError(const std::string& message, const Mpi& mpi, const int threadNumber) 
    : std::runtime_error(mpi.getHostname() + ":" + std::to_string(mpi.getProcessNumber()) + "." + std::to_string(threadNumber) + ": " + message) {}
