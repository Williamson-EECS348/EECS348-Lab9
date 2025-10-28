#pragma once

#include "matrix.h"

#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include <iostream>

template<typename T>
class MatrixReader {
public:
    MatrixReader(const std::string& filename) : file(filename), N(0) {
        try {
            load(filename);
        } catch (const std::exception& e) {
            std::cerr << "Error reading matrix from file: " << e.what() << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    ~MatrixReader() {
        if (file.is_open()) {
            file.close();
        }
    }

    Matrix<T> readMatrix() {
        try {
            return read();
        } catch (const std::exception& e) {
            std::cerr << "Error reading matrix from file: " << e.what() << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

private:
    void load(const std::string& filename) {
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        std::string line;
        // get matrix sizes
        std::getline(file, line);
        N = std::stoul(line);
    }

    Matrix<T> read() {
        Matrix<T> result(N, N);

        std::string line;
        for (size_t i = 0; i < N; ++i) {
            if (!std::getline(file, line)) {
                throw std::runtime_error("Unexpected end of file while reading matrix data.");
            }
            std::istringstream iss(line);
            for (size_t j = 0; j < N; ++j) {
                T value;
                if (!(iss >> value)) {
                    throw std::runtime_error("Invalid matrix data format.");
                }
                result[i][j] = value;
            }
        }
        return result;
    }

    std::ifstream file;
    size_t N;
};