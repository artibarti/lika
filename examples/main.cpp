
#include "../include/lika.hpp"
#include <iostream>

using namespace lika;

template<typename T>
void print(Matrix<T>& matrix) {
  for (size_t rowIdx = 0; rowIdx < matrix.shape().dim(0); rowIdx++) {
    for (size_t colIdx = 0; colIdx < matrix.shape().dim(1); colIdx++) {
      std::cout << " " << matrix.at({rowIdx, colIdx});
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template<typename T>
void multiply2d(const Matrix<T>& a, const Matrix<T>& b, Matrix<T>& result) {
  for (size_t rowIdx = 0; rowIdx < result.shape()[0]; rowIdx++) {
    for (size_t colIdx = 0; colIdx < result.shape()[1]; colIdx++) {
      float sum = 0;
      for (size_t i = 0; i < a.shape()[1]; i++) {
        sum += a.at({rowIdx, i}) * b.at({i, colIdx});
      }
      result.at({rowIdx, colIdx}) = sum;
    }
  }
}



int main(int argc, char** argv) {
    
    std::cout << "Lika matrix library example" << std::endl;

    matrix_d mat_a({2,2});
    matrix_d mat_b({2,2});
    matrix_d mat_c({2,2});

    for (size_t idx = 0; idx < mat_a.size(); idx++) {
      mat_a.at(idx) = 1;
    }
    mat_b.at({0,0}) = 0.9;
    mat_b.at({1,0}) = 0.9;

    for (int i = 0; i < 20; i++) {
      multiply2d(mat_a, mat_b, mat_c);
      print(mat_c);
      mat_b = mat_c;
    }
}
