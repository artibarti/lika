#pragma once

#include <iostream>

namespace lika {

struct Shape2d {

	size_t x, y;

	Shape2d() : x(0), y(0) {}
	Shape2d(size_t x_, size_t y_) : x(x_), y(y_) {}
						
	bool operator==(const Shape2d& other) const {
		return (x == other.x && y == other.y);
	}    

	bool operator!=(const Shape2d& other) const {
		return !(x == other.x && y == other.y);
	}

	size_t size() const {
		return x * y;
	}

	size_t operator[] (size_t idx) const {
		if (idx == 0) {
			return x;
		} else if (idx == 1) {
			return y;
		} else {
			throw std::out_of_range("Invalid argument, Shape2d has only two dimensions");
		}
	}

};

template<typename Stream>
Stream &operator<<(Stream& stream, const Shape2d& shape) {
  stream << shape.x << "x" << shape.y;
  return stream;
}

std::ostream &operator<<(std::ostream& stream, const Shape2d& shape) {
  stream << shape.x << "x" << shape.y;
  return stream;
}

}