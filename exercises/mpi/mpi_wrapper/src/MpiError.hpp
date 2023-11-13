#pragma once

#include <stdexcept>
#include <string>
#include "Mpi.hpp"

class Mpi;

class MpiError : public std::runtime_error {
public:
    explicit MpiError(const std::string& message);
    MpiError(const std::string& message, const Mpi& mpi);
    MpiError(const std::string& message, const Mpi& mpi, const int threadNumber);
};
