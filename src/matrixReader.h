#pragma once

#include "matrix.h" // matrix class definition

#include <cstddef> // needed for size_t
#include <fstream> // needed to read files
#include <sstream> // needed for istringstream
#include <string> // needed for std::string
#include <stdexcept> // needed for exceptions

#include <iostream> // for error output

/**
 * @brief Class to read matrices from a file and return Matrix objects. Designed to handle square matrices
 * @tparam T Type of the matrix elements (e.g. int, float, double, etc.)
 */
template<typename T>
class MatrixReader {
public:
    /**
     * `MatrixReader` constructor that opens the specified file and prepares to read matrices. Calls load to read matrix size
     * @param filename const std::string&; path to the file containing matrix data
     */
    MatrixReader(const std::string& filename) : file(filename), N(0) {
        try { // `load()` can throw an exeption if file cannot be opened so we catch it here
            load(filename);
        } catch (const std::exception& e) { // if an exception is thrown, print error and exit
            std::cerr << "Error reading matrix from file: " << e.what() << std::endl; // print error message
            std::exit(EXIT_FAILURE); // exit program with failure status
        }
    }

    /**
     * `MatrixReader` destructor that closes the file if it is open.
     * We keep the file open for the lifetime of the MatrixReader object to allow multiple reads
     */
    ~MatrixReader() {
        // can't close an unopened file
        if (file.is_open()) // check if file is open
            file.close(); // if it is, close it
    }

    /**
     * Reads a matrix from the file and returns it as a `Matrix<T>` object.
     * Designed to be called multiple times to get all matrices in file
     * @return Matrix<T>; The matrix read from the file
     */
    Matrix<T> readMatrix() { // a wrapper for the read function so the user (me) doesn't need to use a `try` when using it
        try { // `read()` can throw an exeption if file cannot be opened so we catch it here
            return read();
        } catch (const std::exception& e) { // if an exception is thrown, print error and exit
            std::cerr << "Error reading matrix from file: " << e.what() << std::endl; // print error message
            std::exit(EXIT_FAILURE); // exit program with failure status
        }
    }

// private means that the methods cannot be accessed outside the class (unless its a `friend` but ignore that)
private:

    /**
     * 
     * @param filename const std::string&; path to the file containing matrix data
     */
    void load(const std::string& filename) {
        // the file should have been opened in the constructor
        if (!file.is_open()) { // but just to be safe we check that it is
            throw std::runtime_error("Could not open file: " + filename); // if not we throw an error
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