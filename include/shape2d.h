#pragma once

#include <iostream>

namespace lika {

struct Shape2d
{
	unsigned x, y;

	Shape2d() : x(0), y(0) {}
	Shape2d(unsigned _x, unsigned _y) : x(_x), y(_y) {}
						
	bool operator==(const Shape2d& other) const {
		return (x == other.x && y == other.y);
	}    
	bool operator!=(const Shape2d& other) const {
		return !(x == other.x && y == other.y);
	}
	bool operator==(unsigned size) const {
		return (x == size && y == size);
	}    

	unsigned size() const {
		return x * y;
	}

	unsigned operator[] (unsigned index) const {
		if (index == 0) {
			return x;
		} else if (index == 1) {
			return y;
		} else {
			throw std::out_of_range("Invalid argument, Shape2d has only two dimensions");
		}
	}

};

template <typename Stream>
Stream &operator<<(Stream &stream, const Shape2d &shape) {
  stream << shape.x << "x" << shape.y;
  return stream;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, const Shape2d &shape) {
  stream << shape.x << "x" << shape.y;
  return stream;
}


}