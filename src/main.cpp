#include <iostream>

#include "matrix.h"
#include "matrixReader.h"

namespace assignmentFunction {

    template<typename T>
    void print(const Matrix<T>& a, const Matrix<T>& b) {
        std::cout << "Matrix 1:\n" << a << "\nMatrix 2:\n" << b << '\n';
    }

    template<typename T>
    void add(const Matrix<T>& a, const Matrix<T>& b) {
        std::cout << "add:\n" << a + b << '\n';
    }

    template<typename T>
    void multiply(const Matrix<T>& a, const Matrix<T>& b) {
        std::cout << "multiply:\n" << a * b << '\n';
    }

    template<typename T>
    void trace(const Matrix<T>& a) {
        std::cout << "Main Diagonal:" << a.trace()
                  << "\nSecondary Diagonal:" << a.secondaryDiagonalSum() << '\n';
    }

    template<typename T>
    void swapRows(Matrix<T>& a) {
        size_t row1, row2;
        std::cout << "Enter two row indices to swap (single line; seperate with a space): ";
        std::cin >> row1 >> row2;
        if (!a.inRowBounds(row1) || !a.inRowBounds(row2)) {
            std::cerr << "Row indices out of bounds.\n";
            return;
        }

        a.swapRows(row1, row2);
        std::cout << a << '\n';
    }

    template<typename T>
    void swapCols(Matrix<T>& a) {
        size_t col1, col2;
        std::cout << "Enter two column indices to swap (single line; seperate with a space): ";
        std::cin >> col1 >> col2;
        if (!a.inColBounds(col1) || !a.inColBounds(col2)) {
            std::cerr << "Column indices out of bounds.\n";
            return;
        }

        a.swapCols(col1, col2);
        std::cout << a << '\n';
    }

    template<typename T>
    void updateElement(Matrix<T>& a, size_t row, size_t col, const T& value) {
        if (!a.inRowBounds(row) || !a.inColBounds(col)) {
            std::cerr << "Row or column index out of bounds.\n";
            return;
        }

        a[row][col] = value;
        std::cout << a << '\n';
    }
};

int main() {
    MatrixReader<float> reader("matrices.txt");
    auto mat1 = reader.readMatrix();
    auto mat2 = reader.readMatrix();

    assignmentFunction::print(mat1, mat2);
    assignmentFunction::add(mat1, mat2);
    assignmentFunction::multiply(mat1, mat2);
    assignmentFunction::trace(mat1);
    assignmentFunction::swapRows(mat1);
    assignmentFunction::swapCols(mat2);

    std::cout << "Enter row, column and new value (single line; seperate with a space): ";
    size_t row, col;
    float value;
    std::cin >> row >> col >> value;
    assignmentFunction::updateElement(mat1, row, col, value);
}