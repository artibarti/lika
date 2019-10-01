#pragma once

namespace lika {

class Shape2d {

 public:
	size_t rows_, cols_;

	Shape2d() : rows_(0), cols_(0) {}
	Shape2d(size_t rows, size_t cols) : rows_(rows), cols_(cols) {}

	void operator=(const Shape2d& other) {
		rows_ = other.rows_;
		cols_ = other.cols_;
	}

	bool operator==(const Shape2d& other) const {
		return (rows_ == other.rows_ && cols_ == other.cols_);
	}    

	bool operator!=(const Shape2d& other) const {
		return !(rows_ == other.rows_ && cols_ == other.cols_);
	}

	size_t size() const {
		return rows_ * cols_;
	}
};

using shape2d_t = Shape2d;

}