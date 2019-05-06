#include "../include/lika.hpp"
#include <iostream>

using namespace lika;

template<typename T>
void printMatrix(Matrix<T>& matrix) {
  
  for (unsigned rowIndex = 0; rowIndex < matrix.getRowCount(); rowIndex++) {
    for (unsigned colIndex = 0; colIndex < matrix.getColCount(); colIndex++) {
      std::cout << " " << matrix[rowIndex][colIndex];
    }
    std::cout << std::endl;
  }
}

int main(int argc, char** argv)
{
    std::cout << "Lika matrix library example" << std::endl;

    matrix_d mat1(2,5);
    matrix_d mat2(3,4);

    mat1[0][0] = 10;
    mat2[1][2] = 2;

    std::cout << "mat1: " << std::endl;
    printMatrix(mat1);
    std::cout << "mat2: " << std::endl;
    printMatrix(mat2);

}
