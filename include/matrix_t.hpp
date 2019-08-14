#pragma once

#include <memory>
#include <vector>

#include "shape_t.hpp"

namespace lika {

template<typename T>
class Matrix {

  private:
    std::vector<T> matrixData_;
    shape_t shape_;

  public:
    Matrix();
    Matrix(const shape_t& shape);
    Matrix(const std::vector<size_t>& dims);

    Matrix(Matrix<T>&& other);
    Matrix(const Matrix<T>& matrix);
    Matrix<T>& operator= (const Matrix<T>& matrix);

    size_t size() const;
    shape_t shape() const;

    void reshape(const shape_t& shape);
    void reshape(const std::vector<size_t>& dims);

    T* data();
    const T* data() const;

    T& at(size_t idx);
    const T& at(size_t idx) const;
    T& at(const std::vector<size_t>& dims);
    const T& at(const std::vector<size_t>& dims) const;

    bool isEmpty() const;
};

template<typename T>
Matrix<T>::Matrix() {
  reshape(shape_t::nullShape());
}

template<typename T>
Matrix<T>::Matrix(const shape_t& shape) {
  reshape(shape);
}

template<typename T>
Matrix<T>::Matrix(const std::vector<size_t>& dims) {
  reshape(dims);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
  reshape(other.shape_);
  for (size_t elementIdx = 0; elementIdx < other.size(); elementIdx++) {
    matrixData_[elementIdx] = other.matrixData_[elementIdx];
  }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) {
  shape_ = other.shape_;
  matrixData_ = other.matrixData_;
  other.reshape(shape_t::nullShape());
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& other) {
  reshape(other.shape_);
  for (size_t elementIdx = 0; elementIdx < other.size(); elementIdx++) {
    matrixData_[elementIdx] = other.matrixData_[elementIdx];
  }
  return *this;
}

template<typename T>
size_t Matrix<T>::size() const {
  return shape_.size();
}

template<typename T>
shape_t Matrix<T>::shape() const {
  return shape_;
}

template<typename T>
void Matrix<T>::reshape(const std::vector<size_t>& dims) {
  reshape(shape_t(dims));
}

template<typename T>
void Matrix<T>::reshape(const shape_t& shape) {
  if (shape_ != shape) {
    shape_ = shape;    
    matrixData_.resize(shape_.size());
  }
}

template<typename T>
T* Matrix<T>::data() {
  return matrixData_.data();
}

template<typename T>
const T* Matrix<T>::data() const {
  return matrixData_.data();
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
T& Matrix<T>::at(const std::vector<size_t>& dims) {
  return matrixData_[shape_.getIndex(dims)];
}

template<typename T>
const T& Matrix<T>::at(const std::vector<size_t>& dims) const {
  return matrixData_[shape_.getIndex(dims)];
}

template<typename T>
bool Matrix<T>::isEmpty() const {
  return shape_.size() == 0;
}

using matrix_i = Matrix<int>;
using matrix_f = Matrix<float>;
using matrix_d = Matrix<double>;

}