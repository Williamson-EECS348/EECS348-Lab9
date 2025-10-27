#pragma once

#include "matrix.h"

#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include <iostream>

template<typename T>
class FileReader {
public:
    static Matrix<T> readMatrixFromFile(const std::string& filename) {
        try {
            return read(filename);
        } catch (const std::exception& e) {
            std::cerr << "Error reading matrix from file: " << e.what() << std::endl;
            throw;
        }
    }

private:
    static void trimLine(std::string& line) {}

    static Matrix<T> read(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        std::string line;
        // get matrix sizes
        std::getline(file, line);
        size_t N = std::stoul(line);

        std::cout << "Reading a " << N << "x" << N << " matrix from file: " << filename << std::endl;

        Matrix<T> result(N, N);

        return result;
    }
};