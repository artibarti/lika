#pragma once

#include <stdexcept>
#include <vector>

namespace lika {

  class Shape {

    private:
      std::vector<size_t> dims_;
      size_t size_ = 0;

    public:
      Shape();
      Shape(const Shape& other);
      Shape(std::vector<size_t> dims);

      static Shape nullShape();

      size_t size() const;
      size_t dims() const;
      size_t dim(size_t dimIdx) const;
      size_t operator[](size_t dimIdx) const;
      size_t getDimArea(size_t dimIdx) const;

      size_t getIndex(const std::vector<size_t>& indices) const;

      bool operator==(const Shape& other) const;
      bool operator!=(const Shape& other) const;
  };

  Shape::Shape() {}

  Shape::Shape(std::vector<size_t> dims) {
    dims_ = dims;
    size_ = 1;
    for (size_t dimIdx = 0; dimIdx < dims.size(); dimIdx++) {
      size_ *= dims[dimIdx];
      if (dims[dimIdx] == 0) {
        throw std::runtime_error("Size of dimension can not be zero");
      }
    }
  }

  Shape::Shape(const Shape& other) {
    dims_ = other.dims_;
    size_ = other.size_;
  }

  Shape Shape::nullShape() {
    return Shape();
  }

  size_t Shape::size() const {
    return size_;
  }

  size_t Shape::dim(size_t dimIdx) const {
    return dims_[dimIdx];
  }

  size_t Shape::dims() const {
    return dims_.size();
  }

  size_t Shape::getDimArea(size_t dimIdx) const {
    size_t result = 1;
    for (size_t idx = dimIdx + 1; idx < dims_.size(); idx++) {
      result *= dims_[idx];
    }
    return result;
  }

  size_t Shape::getIndex(const std::vector<size_t>& indices) const {
    size_t result = 0;
    for (size_t indiceIdx = 0; indiceIdx < indices.size(); indiceIdx++) {
      size_t dimIdx = dims_.size() - 1 - (indices.size() - indiceIdx - 1);
      result += indices[indiceIdx] * getDimArea(dimIdx);
    }
    return result;
  }

  size_t Shape::operator[](size_t dimIdx) const {
    return dims_[dimIdx];
  }

  bool Shape::operator==(const Shape& other) const {
    if (dims_.size() == other.dims_.size()) {
      for (size_t dimIdx = 0; dimIdx < dims_.size(); dimIdx++) {
        if (dims_[dimIdx] != other.dims_[dimIdx]) {
          return false;
        }
      }
      return true;
    }
    return false;
  }

  bool Shape::operator!=(const Shape& other) const {
    return !operator==(other);
  }

  using shape_t = Shape;
}