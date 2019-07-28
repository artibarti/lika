#pragma once

#include <memory>
#include <vector>
#include "shape2d.hpp"

namespace lika {

template<typename T>
class Matrix {

  private:
    T* matrixData_ = nullptr;
    size_t elementCount_ = 0;
    Shape2d shape_ = Shape2d(0,0);

  public:
    Matrix();
    ~Matrix();
    Matrix(const Matrix<T>& matrix);
    Matrix(Matrix<T>&& other);
    Matrix(Shape2d shape);
    Matrix(size_t rows, size_t cols);
    Matrix<T>& operator= (const Matrix<T>& matrix);

    size_t getElementCount() const;
    size_t rowCount() const;
    size_t colCount() const;
    Shape2d getShape() const;

    void reshape(size_t rows, size_t cols);
    void reshape(const Shape2d shape);

    T* data();
    const T* data() const;

    T& at(size_t idx);
    const T& at(size_t idx) const;
    T& at(size_t rowIdx, size_t colIdx);
    const T& at(size_t rowIdx, size_t colIdx) const;

    void setRow(size_t rowIdx, const std::vector<T>& row);
    void setColumn(size_t colIdx, const std::vector<T>& col);

    bool isEmpty() const;

    bool isMultiplicableWith(const Matrix<T>& other) const;
    bool hasSameDimensionWith(const Matrix<T>& other) const;
};

template<typename T>
Matrix<T>::~Matrix() {
  delete[] matrixData_;
}

template<typename T>
Matrix<T>::Matrix() {
  reshape(0,0);
}

template<typename T>
Matrix<T>::Matrix(Shape2d shape) {
  reshape(shape.x, shape.y);
}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) {
  reshape(rows, cols);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
  reshape(other.rowCount(), other.colCount());
  for (size_t elementIdx = 0; elementIdx < other.elementCount_; elementIdx++) {
    matrixData_[elementIdx] = other.matrixData_[elementIdx];
  }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) {
  shape_ = other.shape_;
  elementCount_ = other.elementCount_;
  matrixData_ = other.matrixData_;
  other.reshape(0,0);
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& other) {
  reshape(other.rowCount(), other.colCount());
  for (size_t elementIdx = 0; elementIdx < other.elementCount_; elementIdx++) {
    matrixData_[elementIdx] = other.matrixData_[elementIdx];
  }
  return *this;
}

template<typename T>
size_t Matrix<T>::getElementCount() const {
  return elementCount_;
}

template<typename T>
size_t Matrix<T>::rowCount() const {
  return shape_.x;
}

template<typename T>
size_t Matrix<T>::colCount()  const {
  return shape_.y;
}

template<typename T>
Shape2d Matrix<T>::getShape() const {
  return shape_;
}

template<typename T>
void Matrix<T>::reshape(size_t rows, size_t cols) {
  
  if (shape_.x != rows || shape_.y != cols) {
    if (matrixData_ != nullptr) {
      delete[] matrixData_;
    }

    elementCount_ = rows * cols;
    shape_ = Shape2d(rows, cols);
    matrixData_ = new T[elementCount_];
  }
}

template<typename T>
void Matrix<T>::reshape(const Shape2d shape) {
  reshape(shape.x, shape.y);
}

template<typename T>
T* Matrix<T>::data() {
  return matrixData_;
}

template<typename T>
const T* Matrix<T>::data() const {
  return matrixData_;
}

template<typename T>
T& Matrix<T>::at(size_t idx) {
  return matrixData_[idx];
}

template<typename T>
const T& Matrix<T>::at(size_t idx) const {
  return matrixData_[idx];
}

template<typename T>
T& Matrix<T>::at(size_t rowIdx, size_t colIdx) {
  return matrixData_[rowIdx*shape_.y + colIdx];
}

template<typename T>
const T& Matrix<T>::at(size_t rowIdx, size_t colIdx) const {
  return matrixData_[rowIdx*shape_.y + colIdx];
}

template<typename T>
void Matrix<T>::setRow(size_t rowIdx, const std::vector<T>& row) {
  if (rowIdx < shape_.x && row.size() == shape_.y) {
    for (size_t colIdx = 0; colIdx < shape_.y; colIdx++) {
      matrixData_[rowIdx * shape_.y + colIdx] = row[colIdx];
    }
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

template<typename T>
void Matrix<T>::setColumn(size_t colIdx, const std::vector<T>& col) {
  if (colIdx < shape_.y && col.size() == shape_.x) {
    for (size_t rowIdx = 0; rowIdx < shape_.x; rowIdx++) {
      matrixData_[rowIdx * shape_.y + colIdx] = col[rowIdx];
    }
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

template<typename T>
bool Matrix<T>::isEmpty() const {
  return shape_ == Shape2d(0,0);
}

template<typename T>
bool Matrix<T>::isMultiplicableWith(const Matrix<T>& other) const {
  return shape_.y == other.rowCount();
}
    
template<typename T>
bool Matrix<T>::hasSameDimensionWith(const Matrix<T>& other) const {
  return shape_.x == other.rowCount() && shape_.y == other.colCount();
}

using matrix_d = Matrix<double>;
using matrix_i = Matrix<int>;

}