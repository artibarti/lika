
#include "../include/lika.hpp"
#include <iostream>

using namespace lika;

template<typename T>
void printMatrix(Matrix<T>& matrix) {
  for (size_t rowIdx = 0; rowIdx < matrix.rowCount(); rowIdx++) {
    for (size_t colIdx = 0; colIdx < matrix.colCount(); colIdx++) {
      std::cout << " " << matrix.at(rowIdx, colIdx);
    }
    std::cout << std::endl;
  }
}

int main(int argc, char** argv) {
    
    std::cout << "Lika matrix library example" << std::endl;

    matrix_d mat1(2,5);
    matrix_d mat2(3,4);

    mat1.at(0, 0) = 10;

    for (size_t rowIdx = 0; rowIdx < mat1.rowCount(); rowIdx++) {
      for (size_t colIdx = 0; colIdx < mat1.colCount(); colIdx++) {
        mat1.at(rowIdx, colIdx) = rowIdx * mat1.rowCount()  + colIdx;
      }
    }

    for (size_t elementIdx = 0; elementIdx < mat2.getElementCount(); elementIdx++) {
      mat2.at(elementIdx) = elementIdx + 2;
    }

    std::cout << "mat1: " << std::endl;
    printMatrix(mat1);
    std::cout << "mat2: " << std::endl;
    printMatrix(mat2);

}
