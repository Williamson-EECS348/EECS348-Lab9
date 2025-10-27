#include <iostream>

#include "matrix.h"
#include "fileReader.h"

int main() {
    Matrix<float> mat = FileReader<float>::readMatrixFromFile("matrices.txt");

    std::cout << mat << std::endl;
}