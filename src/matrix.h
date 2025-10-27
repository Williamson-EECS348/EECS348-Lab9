#pragma once
#include <cstddef>
#include <vector>
#include <iostream>

template<class T>
class Matrix {
public:
    Matrix(int _rows, int _cols)
      : rows(_rows),
        cols(_cols),
        data(_rows, std::vector<T>(_cols, T{})) {}

    Matrix(const Matrix& other)
      : rows(other.rows),
        cols(other.cols),
        data(other.data) {}

    Matrix(std::initializer_list<std::initializer_list<T>> init)
      : rows(init.size()),
        cols(init.begin()->size()),
        data(rows, std::vector<T>(cols)) {
    
        size_t i = 0;
        for (const auto& row : init) {
            size_t j = 0;
            for (const auto& val : row) {
                data[i][j] = val;
                j++;
            }
            i++;
        }
    }

    void setIdentity() {
        if (rows != cols) throw std::invalid_argument("Identity matrix must be square.");

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                data[i][j] = (i == j) ? T{1} : T{0};
            }
        }
    }

    // add (+) and (+=)
    Matrix operator+(const Matrix& other) const {
        // size check
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix& operator+=(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for addition.");
        }

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    // subtract (-) and (-=)
    Matrix operator-(const Matrix& other) const {
        // size check
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }

        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix& operator-=(const Matrix& other) {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrix dimensions must match for subtraction.");
        }

        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    // multiply (*) and (*=)
    Matrix operator*(const Matrix& other) const {
        // size check
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions do not allow multiplication.");
        }

        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * other.data[i][j];
            }
        }
        return result;
    }

    Matrix& operator*=(const Matrix& other) {
        if (cols != other.rows) {
            throw std::invalid_argument("Matrix dimensions do not allow multiplication.");
        }

        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * other.data[i][j];
            }
        }
        *this = std::move(result);
        return *this;
    }

    // sum of diagonal elements
    T trace() const {
        if (rows != cols) {
            throw std::invalid_argument("Trace is only defined for square matrices.");
        }
        T sum = T{};
        for (size_t i = 0; i < rows; i++) {
            sum += data[i][i];
        }
        return sum;
    }

    // Swap matrix rows
    // Implement a function that takes a matrix and two-row indices as input (with indexing starting at 0). If both indices are within valid bounds, swap the specified rows and output the resulting matrix.
    void swapRows(size_t row1, size_t row2) {
        if (row1 >= rows || row2 >= rows) return;
        for (size_t j = 0; j < cols; j++) {
            std::swap(data[row1][j], data[row2][j]);
        }
    }

    // Swap matrix columns
    // Implement a function that takes a matrix and two-column indices as input (with indexing starting at 0). If both indices are within valid bounds, swap the specified rows and output the resulting matrix.
    void swapCols(size_t col1, size_t col2) {
        if (col1 >= cols || col2 >= cols) return;
        for (size_t i = 0; i < rows; i++) {
            std::swap(data[i][col1], data[i][col2]);
        }
    }

    // transpose
    Matrix transpose() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    // determinant
    T determinant() const {
        if (rows != cols) {
            throw std::invalid_argument("Determinant is only defined for square matrices.");
        }
        // This is a placeholder implementation for 2x2 matrices.
        if (rows == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        } else {
            // For larger matrices, a full implementation would be needed.
            throw std::logic_error("Determinant not implemented for matrices larger than 2x2.");
        }
    }

public:
    // Assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (size_t i = 0; i < rows; i++) {
                for (size_t j = 0; j < cols; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    std::vector<T>& operator[](size_t row) { return data.at(row); }
    const std::vector<T>& operator[](size_t row) const { return data.at(row); }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        for (size_t i = 0; i < m.rows; i++) {
            for (size_t j = 0; j < m.cols; j++) {
                os << m.data[i][j] << " ";
            }
            os << "\n";
        }
        return os;
    }

    // Getter methods for dimensions
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

private:
    size_t rows, cols;
    std::vector<std::vector<T>> data;
};