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
     * starts loading a file and finds the matrix size
     * @param filename const std::string&; path to the file containing matrix data
     */
    void load(const std::string& filename) {
        // the file should have been opened in the constructor
        if (!file.is_open()) { // but just to be safe we check that it is
            throw std::runtime_error("Could not open file: " + filename); // if not we throw an error
        }

        /*** get matrix sizes ***/
        std::string line; // the string to hold each line as we read it
        std::getline(file, line); // get the first line on the file since it holds the NxN size of the matrix
        N = std::stoul(line); // convert the string to an `unsigned long` (aka a `size_t`) and store that in the member variable `N`
    }

    /**
     * Reads the next matrix from the file and gives back to the user the `Matrix<T>`
     * with the new matrix data
     * @return Matrix<T>; the (NxN) matrix that was read in from the file
     */
    Matrix<T> read() {
        Matrix<T> result(N, N); // the matrix to return

        std::string line; // the string to hold each line as we read it
        for (size_t i = 0; i < N; i++) { // we assume input is valid and loop only enough for a square matrix (i.e. up to `N`)
            // reads the file from where we last left it and gets the new line
            if (!std::getline(file, line)) { // if the line is empty we throw an error
                // we expect at least enough data to fill an NxN matrix so if we dont get that much data then we throw an error
                throw std::runtime_error("Unexpected end of file while reading matrix data.");
            }

            // string stream to read out the line in the file as an input stream
            std::istringstream iss(line); // automatically deliminates on white space and converts to `T`
            for (size_t j = 0; j < N; j++) { // again, we assume we only need to loop enough for a square matrix
                T value; // the value that we will assign to the matrix cell, we make it type `T` since that is also the type of the matrix
                if (!(iss >> value)) { // read the next 'part' of the `stringstream` into value; if this fails we throw an error
                    // if we cannot read the data into the `value` then there must be some error in the incomming data and we throw an error
                    throw std::runtime_error("Invalid matrix data format.");
                }
                result[i][j] = value; // assign the value we found to cell in the matrix
            }
        }
        // return the result to the user, this is pretty expensive since its copying multiple vectors
        // so it would be better to use something like a smart pointer (i.e. `unique_ptr`) but oh well
        return result;
    }

    std::ifstream file; // the file which holds the matrix
    size_t N; // the size of the matrix
};