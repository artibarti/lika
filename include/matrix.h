#pragma once

#include <memory>

#include "shape2d.h"
#include "access_rule.h"
#include "limited_access_matrix.h"

namespace lika {

template<typename T>
class Matrix {

  private:
    std::shared_ptr<T> matrixData_;
    unsigned elementCount_;
    Shape2d shape_;
    
    AccessRule getAccessRuleForRow(unsigned rowIndex);

  public:
    Matrix() {}
    Matrix(Shape2d shape);
    Matrix(const Matrix<T>& other);
    Matrix(unsigned rows, unsigned cols);
    Matrix<T>& operator= (const Matrix<T>& other);

    unsigned getElementCount() const;
    unsigned rowCount() const;
    unsigned colCount() const;
    Shape2d getShape() const;

    void reshape(unsigned rows, unsigned cols);
    void reshape(const Shape2d shape);

    T* data();
    const T* data() const;

    T& getElement(unsigned rowIndex, unsigned colIndex);
    const T& getElement(unsigned rowIndex, unsigned colIndex) const;

    LimitedAccessMatrix<T> operator[] (unsigned rowIndex);
    const LimitedAccessMatrix<T> operator[] (unsigned rowIndex) const;

    T& at(unsigned index);
    const T& at(unsigned index) const;

    void setRow(unsigned rowIndex, const std::vector<T>& row);
    void setColumn(unsigned colIndex, const std::vector<T>& col);

    bool isEmpty() const;

    bool isMultiplicableWith(const Matrix<T>& other) const;
    bool hasSameDimensionWith(const Matrix<T>& other) const;
};

template<typename T>
Matrix<T>::Matrix(Shape2d shape) {
  reshape(shape);
}

template<typename T>
Matrix<T>::Matrix(unsigned rows, unsigned cols) {
  reshape(rows, cols);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
  reshape(other.shape_);
  for (unsigned rowIndex = 0; rowIndex < other.elementCount_; rowIndex++) {
    matrixData_.get()[rowIndex] = other.matrixData_.get()[rowIndex];
  }
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& other) {
  reshape(other.rowCount(), other.colCount());
  for (unsigned rowIndex = 0; rowIndex < other.elementCount_; rowIndex++) {
    matrixData_.get()[rowIndex] = other.matrixData_.get()[rowIndex];
  }
  return *this;
}

template<typename T>
unsigned Matrix<T>::getElementCount() const {
  return elementCount_;
}

template<typename T>
unsigned Matrix<T>::rowCount() const {
  return shape_.x;
}

template<typename T>
unsigned Matrix<T>::colCount()  const {
  return shape_.y;
}

template<typename T>
Shape2d Matrix<T>::getShape() const {
  return shape_;
}

template<typename T>
void Matrix<T>::reshape(unsigned rows, unsigned cols) {  
  
  if (shape_.x != rows || shape_.y != cols) {
    elementCount_ = rows * cols;
    shape_ = Shape2d(rows, cols);
    matrixData_ = std::shared_ptr<T>(new T[elementCount_], [&](T* ptr){ delete[] ptr; });
  }
}

template<typename T>
void Matrix<T>::reshape(const Shape2d shape) {
  reshape(shape.x, shape.y);
}

template<typename T>
T* Matrix<T>::data() {
  return matrixData_.get();
}

template<typename T>
const T* Matrix<T>::data() const {
  return matrixData_.get();
}

template<typename T>
T& Matrix<T>::getElement(unsigned row, unsigned col) {
  if (row < shape_.x && col < shape_.y) {
    return matrixData_.get()[row * shape_.y + col];
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

template<typename T>
const T& Matrix<T>::getElement(unsigned row, unsigned col) const {
  if (row < shape_.x && col < shape_.y) {
    return matrixData_.get()[row * shape_.y + col];
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

template<typename T>
LimitedAccessMatrix<T> Matrix<T>::operator[] (unsigned rowIndex) {
  if (rowIndex < shape_.x) {
    LimitedAccessMatrix<T> result(matrixData_, getAccessRuleForRow(rowIndex));
    return result;
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

template<typename T>
const LimitedAccessMatrix<T> Matrix<T>::operator[] (unsigned rowIndex) const {
  if (rowIndex < shape_.x) {
    LimitedAccessMatrix<T> result(matrixData_, getAccessRuleForRow(rowIndex));
    return result;
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

template<typename T>
T& Matrix<T>::at(unsigned index) {
  if (index < elementCount_) {
    return matrixData_.get()[index];
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

template<typename T>
const T& Matrix<T>::at(unsigned index) const {
  if (index < elementCount_) {
    return matrixData_.get()[index];
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

template<typename T>
void Matrix<T>::setRow(unsigned rowIndex, const std::vector<T>& row) {
  if (rowIndex < shape_.x && row.size() == shape_.y) {
    for (unsigned colIndex = 0; colIndex < shape_.y; colIndex++) {
      matrixData_.get()[rowIndex * shape_.y + colIndex] = row[colIndex];
    }
  } else {
    throw std::out_of_range("Index out of bounds");
  }
}

template<typename T>
void Matrix<T>::setColumn(unsigned colIndex, const std::vector<T>& col) {
  if (colIndex < shape_.y && col.size() == shape_.x) {
    for (unsigned rowIndex = 0; rowIndex < shape_.x; rowIndex++) {
      matrixData_.get()[rowIndex * shape_.y + colIndex] = col[rowIndex];
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
  return shape_.y == other.shape_.x;
}
    
template<typename T>
bool Matrix<T>::hasSameDimensionWith(const Matrix<T>& other) const {
  return shape_.x == other.shape_.x && shape_.y == other.shape_.y;
}

template<typename T>
AccessRule Matrix<T>::getAccessRuleForRow(unsigned rowIndex) {
  return AccessRule(rowIndex * shape_.y, (rowIndex+1) * shape_.y - 1, 1);
}

using matrix_i = Matrix<int>;
using matrix_f = Matrix<float>;
using matrix_d = Matrix<double>;

}