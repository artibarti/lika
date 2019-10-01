
#include "../include/lika.hpp"
#include <iostream>

using namespace lika;

template<typename T>
void print(Matrix<T>& matrix) {
  for (size_t rowIdx = 0; rowIdx < matrix.rows(); rowIdx++) {
    for (size_t colIdx = 0; colIdx < matrix.cols(); colIdx++) {
      std::cout << " " << matrix.at(rowIdx, colIdx);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template<typename T>
void multiply(const Matrix<T>& left, const Matrix<T>& right, Matrix<T>& result) {
  for (size_t rowIdx = 0; rowIdx < result.rows(); rowIdx++) {
    for (size_t colIdx = 0; colIdx < result.cols(); colIdx++) {
      float sum = 0;
      for (size_t i = 0; i < left.cols(); i++) {
        sum += left.at(rowIdx, i) * right.at(i, colIdx);
      }
      result.at(rowIdx, colIdx) = sum;
    }
  }
}



int main(int argc, char** argv) {
    
    std::cout << "Lika matrix library example" << std::endl;

    matrix_d mat_a(2,2);
    matrix_d mat_b(2,2);
    matrix_d mat_c(2,2);

    for (size_t idx = 0; idx < mat_a.size(); idx++) {
      mat_a.at(idx) = 1;
    }
    mat_b.at(0,0) = 0.9;
    mat_b.at(1,1) = 0.9;

    for (int i = 0; i < 20; i++) {
      multiply(mat_a, mat_b, mat_c);
      print(mat_c);
      mat_b = mat_c;
    }
}
