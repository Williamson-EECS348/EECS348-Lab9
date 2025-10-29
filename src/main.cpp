#include <iostream> // needed for std::cout, std::cin, std::endl
#include <string> // needed for std::string

#include "matrixReader.h" // include the MatrixReader class

/**
 * Namespace that holds all the functions for the assignment
 * They were uncomfortably precise in their requirements so I put them all in here to interface with my matrix class
 *      I want the matrix class to be reusable and not tied to a specific assignment
 */
namespace assignmentFunction {

    /**
     * Print the matrices with proper formatting, such as aligned columns
     * @tparam T type of the matrix elements
     * @param a const Matrix reference to the first matrix to be printed
     * @param b const Matrix reference to the second matrix to be printed
     */
    template<typename T>
    void print(const Matrix<T>& a, const Matrix<T>& b) {
        // print the two matrices with labels
        std::cout << "Matrix 1:\n" << a << "\nMatrix 2:\n" << b << '\n';
    }

    /**
     * Implement a function that adds two matrices and displays the resulting matrix
     * @tparam T type of the matrix elements
     * @param a const Matrix reference to the first matrix to be added
     * @param b const Matrix reference to the second matrix to be added
     */
    template<typename T>
    void add(const Matrix<T>& a, const Matrix<T>& b) {
        // print the sum of the two matrices
        // uses the overloaded + operator and the overloaded << operator for printing
        std::cout << "add:\n" << a + b << '\n';
    }

    /**
     * Implement a function that multiplies two matrices and displays the resulting matrix
     * @tparam T type of the matrix elements
     * @param a const Matrix reference to the first matrix to be multiplied
     * @param b const Matrix reference to the second matrix to be multiplied
     */
    template<typename T>
    void multiply(const Matrix<T>& a, const Matrix<T>& b) {
        // print the product of the two matrices
        // uses the overloaded * operator and the overloaded << operator for printing
        std::cout << "multiply:\n" << a * b << '\n';
    }

    /**
     * Implement a function to calculate and display the sum of the main and secondary diagonal elements of a matrix
     * @tparam T type of the matrix elements
     * @param a const Matrix reference to the matrix whose diagonals will be summed
     */
    template<typename T>
    void trace(const Matrix<T>& a) {
        // print the sums of the main and secondary diagonals

        std::cout << "Main Diagonal:" << a.trace() // print the sum of the main diagonal
                  << "\nSecondary Diagonal:" << a.secondaryDiagonalSum() << '\n'; // print the sum of the secondary diagonal
    }

    /**
     * Implement a function that takes a matrix and two-row indices as input (with indexing starting at 0).
     * If both indices are within valid bounds, swap the specified rows and output the resulting matrix
     * @tparam T type of the matrix elements
     * @param a const Matrix reference to the matrix whose rows will be swapped
     * @param row1 size_t index of the first row to be swapped
     * @param row2 size_t index of the second row to be swapped
     */
    // we want to use a reference here since we are modifying the matrix and dont want to make a copy
    template<typename T>
    void swapRows(Matrix<T>& a, size_t row1, size_t row2) {
        // check that the row indices are in bounds
        if (!a.inRowBounds(row1) || !a.inRowBounds(row2)) {
            // if not, print error
            std::cerr << "Row indices out of bounds.\n";
            return; // and return
        }

        a.swapRows(row1, row2); // swap the rows using the member function
        std::cout << a << '\n'; // print the modified matrix
    }

    /**
     * Implement a function that takes a matrix and two-column indices as input (with indexing starting at 0).
     * If both indices are within valid bounds, swap the specified columns and output the resulting matrix.
     * @tparam T type of the matrix elements
     * @param a the Matrix reference to the matrix whose columns will be swapped
     * @param col1 size_t index of the first column to be swapped
     * @param col2 size_t index of the second column to be swapped
     */
    template<typename T>
    void swapCols(Matrix<T>& a, size_t col1, size_t col2) {
        // we want to use a reference for Matrix<T> here since we are modifying the matrix and dont want to make a copy

        // check that the column indices are in bounds
        if (!a.inColBounds(col1) || !a.inColBounds(col2)) {
            std::cerr << "Column indices out of bounds.\n"; // if not print error
            return; // and return
        }

        a.swapCols(col1, col2); // swap the columns using the member function
        std::cout << a << '\n'; // print the modified matrix
    }

    /**
     * Implement a function that accepts a matrix, a row index, a column index, and a new value.
     * If both indices are valid (with indexing starting at 0),
     * update the element at the specified position and display the resulting matrix.
     * @tparam T type of the matrix elements
     * @param a the Matrix reference to be updated
     * @param row size_t index of the row of the element to be updated
     * @param col size_t index of the column of the element to be updated
     * @param value the new value to be set at the specified position
     */
    template<typename T>
    void updateElement(Matrix<T>& a, size_t row, size_t col, const T& value) {
        // we want to use a reference for Matrix<T> here since we are modifying the matrix and dont want to make a copy

        // check that the row and column indices are in bounds
        if (!a.inRowBounds(row) || !a.inColBounds(col)) {
            std::cerr << "Row or column index out of bounds.\n"; // if not print error
            return; // and return
        }

        a[row][col] = value; // update the element using the overloaded [] operator
        std::cout << a << '\n'; // print the modified matrix
    }
};

// required main function entry point for C/C++ programs
int main() {
    std::string filename{}; // string to hold the filename
    std::cout << "Enter the matrix file name: "; // prompt user for file name
    std::cin >> filename; // read the filename from user input
    MatrixReader<int> reader(filename); // create a MatrixReader to read int matrices from the file

    auto mat1 = reader.readMatrix(); // read the first matrix from the file and store it
    auto mat2 = reader.readMatrix(); // read the second matrix from the file and store it

    assignmentFunction::print(mat1, mat2); // print the two matrices
    assignmentFunction::add(mat1, mat2); // add the two matrices and print the result
    assignmentFunction::multiply(mat1, mat2); // multiply the two matrices and print the result
    assignmentFunction::trace(mat1); // calculate and print the traces of the first matrix

    size_t row1, row2; // variables to hold the row indices
    std::cout << "Enter two row indices to swap (single line; seperate with a space): "; // prompt user for row indices
    std::cin >> row1 >> row2; // read the row indices from user input
    assignmentFunction::swapRows(mat1, row1, row2); // swap the specified rows in the first matrix and print the result

    size_t col1, col2; // variables to hold the column indices
    std::cout << "Enter two column indices to swap (single line; seperate with a space): "; // prompt user for column indices
    std::cin >> col1 >> col2; // read the column indices from user input
    assignmentFunction::swapCols(mat2, col1, col2); // swap the specified columns in the second matrix and print the result

    std::cout << "Enter row, column and new value (single line; seperate with a space): "; // prompt user for row, column and new value
    size_t row, col; // variables to hold the row and column indices
    int value; // variable to hold the new value
    std::cin >> row >> col >> value; // read the row, column and new value from user input
    assignmentFunction::updateElement(mat1, row, col, value); // update the specified element in the first matrix and print the result
}