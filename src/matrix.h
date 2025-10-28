#pragma once // header guard

#include <cstddef> // needed for `size_t`
#include <vector> // needed for `std::vector` which we use to make the matrix
#include <iostream> // needed to both print and to get interface with the `<<` operator
#include <initializer_list> // needed for the initializer list constructor
#include <utility> // needed for std::swap
#include <stdexcept> // needed for throwing errors

/**
 * The matrix class with many matrix operations defined; uses operator overloading
 * @tparam T the type of the matrix, can be almost anything as long as it has standard operators defined (should probably be a standard number type however)
 * @author Jack Williamson
 * @date 10-27-2025
 */
template<class T>
class Matrix {
    // the default for a class is private so we dont need to put the private header here
    typedef std::vector<T> row_t; // a typedef so that the vector<T> can be shorter and have a more descriptive name
    // equiv `std::vector<std::vector<T>>`
    typedef std::vector<row_t> mat_t; // typedef of the double vector, even shorter and more descriptive

public:

    /**
     * @brief Construct a new (empty) Matrix object
     * @param _rows the number of rows to the matrix
     * @param _cols the number of cols to the matrix
     */
    Matrix(int _rows, int _cols)
      : rows(_rows), // init the rows; counting starts at 1
        cols(_cols), // init the cols; counting starts at 1
        // init the data vectors
        // init the mat_t vector with size of `_rows` and default init of:
        //  row_t vector with size of `cols` and `T` with default initlization
        data(_rows, row_t(_cols, T{})) {}

    /**
     * assignment operator
     * @param other the matrix to be assigned to `this` one
     * @return Matrix& reference to `this` matrix after assignment
     */
    Matrix& operator=(const Matrix& other) {
        if (this != &other) { // protect against self-assignment
            rows = other.rows; // copy rows
            cols = other.cols; // copy cols
            data = other.data; // copy data; vector has its own assignment operator so this works fine
        }
        return *this; // return reference to this object
    }

    /**
     * Addition operator (+) => (Matrix<T> + Matrix<T>)
     * Adds to matrices together and gives result
     * @param other the matrix to be added to `this` one
     * @return Matrix; new matrix which holds the sum
     */
    Matrix operator+(const Matrix& other) const {
        // Can only add matrices of the same size so we check that we can
        if (rows != other.rows || cols != other.cols) {
            // if we cannont then throw an error and tell user
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        // the matrix which holds the sum of the added matrices
        Matrix result(rows, cols);
        for (size_t row = 0; row < rows; row++) { // loop through every row
            for (size_t col = 0; col < cols; col++) { // loop through every col
                result.data[row][col] = data[row][col] + other.data[row][col]; // add cells and assign them to the result
            }
        }
        return result; // return copy of result to user
    }

    /**
     * Multiplies to matrices together and returns their product
     * @param other the matrix to be multiplied to `this` one
     * @return Matrix new matrix which holds the product
     */
    Matrix operator*(const Matrix& other) const {
        // Matrix multiplication needs the left matrix cols to be equal to the right's row number
        if (cols != other.rows) { // if the matrices are improperly sized for multiplication
            // throw error to the user
            throw std::invalid_argument("Matrix dimensions do not allow multiplication.");
        }

        Matrix result(rows, other.cols); // make properly sized matrix
        for (size_t i = 0; i < rows; i++) { // loop through every row of this
            for (size_t j = 0; j < other.cols; j++) { // loop through every col of other
                result.data[i][j] = T{}; // set the current index to be the default init
                for (size_t k = 0; k < cols; k++) { // then loop through every col of this
                    result.data[i][j] += data[i][k] * other.data[k][j]; // follow the matrix multiplication formula and store results
                }
            }
        }
        return result; // return copy of result to user
    }

    /**
     * Trace is the main diagonal sum (top left to bottom right)
     * @return T the sum of the main diagonal cells
     */
    T trace() const { // trace makes no change to the class so we can call it const so it can be used by const objects
        // trace can only be done on a square matrix so we check that it is one
        if (rows != cols) {
            // if not throw an error
            throw std::invalid_argument("Trace is only defined for square matrices.");
        }

        // the sum needs to be the matrix type since its the sum of all the elements
        T sum{}; // default init it so its not undefined
        for (size_t i = 0; i < rows; i++) { // loop through; we only need a single loop since we are just looping the diagonal
            sum += data[i][i]; // add up all diagonal elements
        }
        return sum; // return sum to user
    }

    /**
     * Calculates the secondary diagonal sum (top right to bottom left)
     * @return T the sum of the secondary diagonal cells
     */
    T secondaryDiagonalSum() const {
        // same as before; can only be preformed on a square matrix
        if (rows != cols) {
            // throw error if not
            throw std::invalid_argument("Secondary diagonal sum is only defined for square matrices.");
        }

        // the sum needs to be the matrix type since its the sum of all the elements
        T sum{}; // default init it so its not undefined
        for (size_t i = 0; i < rows; i++) // loop through; we only need a single loop since we are just looping the diagonal
            sum += data[i][(cols - 1) - i]; // add up all secondary diagonal elements; the `(cols - 1) - i` is the formula to find the oposite diagonal
        return sum; // return sum
    }

    /**
     * Swaps two rows of the matrix
     * @param row1 the index of the first row
     * @param row2 the index of the second row
     */
    void swapRows(size_t row1, size_t row2) {
        // check if indices are in bound,  if not do nothing
        if (inRowBounds(row1) || inRowBounds(row2)) return;

        for (size_t j = 0; j < cols; j++) { // loop through every col
            std::swap(data[row1][j], data[row2][j]); // swap the elements in the two rows; we use std::swap to make it easier
        }
    }

    // Swap matrix columns
    // Implement a function that takes a matrix and two-column indices as input (with indexing starting at 0). If both indices are within valid bounds, swap the specified rows and output the resulting matrix.
    /**
     * Swaps two columns of the matrix
     * @param col1 the index of the first column
     * @param col2 the index of the second column
     */
    void swapCols(size_t col1, size_t col2) {
        // check if indices are in bound, if not do nothing
        if (inColBounds(col1) || inColBounds(col2)) return;

        for (size_t i = 0; i < rows; i++) { // loop through every row
            std::swap(data[i][col1], data[i][col2]); // swap the elements in the two columns; we use std::swap to make it easier
        }
    }

    /**
     * Access operator to get a specific row of the matrix; allows for double indexing like `matrix[row][col]`
     * @param row the row index to access
     * @return row_t& reference to the specified row
     */
    row_t& operator[](size_t row) {
        // use at() to get bounds checking for "free"
        return data.at(row);
    }

    /**
     * Access operator to get a specific row of the matrix; allows for double indexing like `matrix[row][col]`.
     * This is the const version which is called on const Matrix objects 
     * @param row the row index to access
     * @return const row_t& reference to the specified row
     */
    const row_t& operator[](size_t row) const {
        // use at() to get bounds checking for "free"
        return data.at(row);
    }

    /**
     * Overloaded output stream operator for Matrix class so we can print it easily using `std::cout << matrix;`
     * This is a friend function so it can access private members of the class, but is not a member function itself
     * its just set up this way to work with the `<<` operator
     * @param os the output stream
     * @param m the matrix to output
     * @return std::ostream& reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        // we need to acess the private members of Matrix so we make this a friend function
        for (size_t i = 0; i < m.rows; i++) { // loop through every row
            os << "|\t"; // print left border; tabbed for formatting
            for (size_t j = 0; j < m.cols; j++) { // loop through every col
                os << m.data[i][j] << "\t"; // print the element followed by a tab for formatting
            }
            os << "|\n"; // print right border and newline
        }
        return os; // return the output stream
    }

    // helper functions to check if indices are in bounds
    // just checks if the given row/col is within the matrix bounds [0, rows) or [0, cols)
    bool inRowBounds(size_t row) const { return row < rows && row >= 0; }
    bool inColBounds(size_t col) const { return col < cols && col >= 0; }

private: // private members; cannot be accessed outside the class (except by friends)
    size_t rows, cols; // dimensions of the matrix
    mat_t data; // the actual matrix data stored as a vector of vectors
};