#ifndef MPISTREAM_HPP
#define MPISTREAM_HPP

#include <sstream>
#include <mpi.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

#include "Mpi.hpp"

class Mpi;

///// Doesnt work. Couldnt figure out why. /////
// Implementation on Mpi.hpp was commented to not make the other exercises fail.

class MpiStream {
public:
    MpiStream(int targetProcess, Mpi& mpi) : targetProcess(targetProcess), mpi(mpi) {
        if (targetProcess < 0 || targetProcess >= mpi.getProcessCount()) {
            throw std::out_of_range("Invalid target process number");
        }
    }

    // Copy constructor
    MpiStream(const MpiStream& other) : targetProcess(other.targetProcess), mpi(other.mpi) {
        // Copy the content of the stringstream
        ss.str(other.ss.str());
    }

    ~MpiStream() {
        // Enviar el string al proceso correspondiente
        mpi.send(ss.str(), targetProcess);
    }

    // Operador <<.
    template <typename T>
    MpiStream& operator<<(const T& value) {
        std::stringstream ss;
        ss << value;
        mpi.send(ss.str(), targetProcess);
        return *this;
    }

    // Operador >>.
    template <typename T>
    MpiStream& operator>>(T& value) {
        std::string serializedValue;
        mpi.receive(serializedValue, targetProcess);
        std::istringstream iss(serializedValue);
        iss >> value;
        return *this;
    }

private:
    int targetProcess;
    Mpi& mpi;
    std::stringstream ss;  // Para acumular el string.
};

#endif // MPISTREAM