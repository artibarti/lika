#pragma once

#include <memory>
#include <vector>

namespace lika {

/**
 * Matrix row and column vector abstraction.
 * Provides a limited access to the matrix elements by hiding true indexing.
 */
template< typename T>
class LimitedAccessMatrix {

 private:
  std::shared_ptr<T> data_;
  std::vector<unsigned> accessibleIndices_;
  unsigned size_;

 public:
  LimitedAccessMatrix();
  LimitedAccessMatrix(std::shared_ptr<T> data, const std::vector<unsigned>& accessibleIndices);
  LimitedAccessMatrix& operator= (const std::vector<T>& other);

  T& operator[] (unsigned index);
  const T& operator[] (unsigned index) const;

  unsigned getSize() const;
};

using vector_i = LimitedAccessMatrix<int>;
using vector_f = LimitedAccessMatrix<float>;
using vector_d = LimitedAccessMatrix<double>;

template<typename T>
LimitedAccessMatrix<T>::LimitedAccessMatrix() {}

template<typename T>
LimitedAccessMatrix<T>::LimitedAccessMatrix(std::shared_ptr<T> data, const std::vector<unsigned>& accessibleIndices) {
  data_ = data;
  accessibleIndices_ = accessibleIndices;
  size_ = accessibleIndices_.size();
}

template<typename T>
LimitedAccessMatrix<T>& LimitedAccessMatrix<T>::operator= (const std::vector<T>& other) {
  if (other.size() != size_) {
    throw std::runtime_error("Vectors have different dimensions");
  } else {
    for (unsigned index = 0; index < size_; index++) {
      data_.get()[accessibleIndices_[index]] = other[index];
    }
  }
  return *this;
}

template<typename T>
T& LimitedAccessMatrix<T>::operator[] (unsigned index) {
  if (index < size_) {
    return data_.get()[accessibleIndices_[index]];
  } else {
    throw std::runtime_error("Vectors have different dimensions");
  }
}

template<typename T>
const T& LimitedAccessMatrix<T>::operator[] (unsigned index) const {
  if (index < size_) {
    return data_.get()[accessibleIndices_[index]];
  } else {
    throw std::runtime_error("Vectors have different dimensions");
  }
}

template<typename T>
unsigned LimitedAccessMatrix<T>::getSize() const {
  return size_;
}

}