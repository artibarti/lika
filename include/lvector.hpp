
#ifndef LIKA_VECTOR_H
#define LIKA_VECTOR_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <boost/type_index.hpp>

namespace Lika 
{
	template<typename T, int S>
	class Vector 
	{
		private:
			int size = S;
			std::vector<T> values;
						
		public:
			Vector();
			Vector(std::initializer_list<T> il);
			Vector(T t);

			int getSize();
			std::vector<T> getValues() const;
			T get(int index) const;
			double getNorm() const;
			double getDistanceFrom(const Vector& v);

			T& operator[] (int index);
			void setValues(std::vector<T> values_);

			Vector<T,S>& normalize();
			Vector<T,S>& reverse();
			Vector<T,S>& operator= (const Vector& v);
			Vector<T,S>& operator= (std::initializer_list<T> il);
			Vector<T,S> operator+ (const Vector<T,S>& v) const;
			Vector<T,S> operator- (const Vector<T,S>& v) const;
			
			void showInfo();
	};

	template<typename T, int S>
	Vector<T,S>::Vector()
	{
		for (int i = 0; i<size; i++)
			values.push_back(0);
	}

	template<typename T, int S>
	Vector<T,S>::Vector(T t)
	{
		for (int i = 0; i<size; i++)
			values.push_back(t);
	}

	template<typename T, int S>
	Vector<T,S>::Vector(std::initializer_list<T> il)
	{
		if (il.size() == S)
			values = il;
		else
			throw std::invalid_argument( "initializer list size does not correspond for this type" );
	}

	template<typename T, int S>
	int Vector<T,S>::getSize()
	{
		return size;
	}

	template<typename T, int S>
	double Vector<T,S>::getDistanceFrom(const Vector<T,S>& v)
	{
		v-*this;
		return (v-*this).getNorm();
	}

	template<typename T, int S>
	double Vector<T,S>::getNorm() const
	{
		double retrunVal = 0;

		for (int i = 0; i < size; i++)
		{
			retrunVal += pow(abs(values[i]), 2);
		}

		return pow(retrunVal, 0.5);
	}

	template<typename T, int S>
	std::vector<T> Vector<T,S>::getValues() const
	{
		return values;
	}

	template<typename T, int S>
	T& Vector<T,S>::operator[] (int index)
	{
		if (size > index && index >= 0)
			return values[index];
		else 
			throw std::invalid_argument( "index value is out of bounds" );
	}

	template<typename T, int S>
	T Vector<T,S>::get(int index) const
	{
		if (size > index && index >= 0)
			return values[index];
		else 
			throw std::invalid_argument( "index value is out of bounds" );
	}

	template<typename T, int S>
	void Vector<T,S>::setValues(std::vector<T> values_)
	{
		if (values_.size() == size)
			values = values_;
		else
			throw std::invalid_argument( "argument does not correspond fot this type " );
	}

	template<typename T, int S>
	Vector<T,S>& Vector<T,S>::operator= (const Vector<T,S>& v)
	{
		values.clear();
		for (int i = 0; i<size; i++)
			values.push_back(v.getValues()[i]);
		return *this;
	}

	template<typename T, int S>
	Vector<T,S>& Vector<T,S>::operator= (std::initializer_list<T> il)
	{
		values.clear();
		if (il.size() == S)
			values = il;
		else
			throw std::invalid_argument( "initializer list size does not correspond fot this type" );
	}

	template<typename T, int S>
	Vector<T,S> Vector<T,S>::operator+ (const Vector& v) const
	{
		Vector<T,S> result;

		for (int i = 0; i < size; i++)
		{
			result[i] = values[i] + v.get(i);
		}		

		return result;
	}

	template<typename T, int S>
	Vector<T,S> Vector<T,S>::operator- (const Vector& v) const
	{
		Vector<T,S> result;

		for (int i = 0; i < size; i++)
		{
			result[i] = v.get(i) - this->get(i);
		}		

		return result;
	}

	template<typename T, int S>
	Vector<T,S>& Vector<T,S>::normalize()
	{
		double norm = getNorm();
		std::for_each(values.begin(), values.end(), [norm](T& t) {t /= norm; });
		return *this;
	}

	template<typename T, int S>
	Vector<T,S>& Vector<T,S>::reverse ()
	{
		std::reverse(values.begin(),values.end());
		return *this;
	}

	template<typename T, int S>
	void Vector<T,S>::showInfo()
	{
		std::cout << "Vector of type " << boost::typeindex::type_id<T>().pretty_name() 
			<< " and size of " << S << std::endl;

		for (int i = 0; i<size; i++)
		{
			std::cout << values[i] << "  ";
		}
		std::cout << std::endl;
	}


	typedef Vector<int, 2> vec2i;
	typedef Vector<int, 3> vec3i;
	typedef Vector<int, 4> vec4i;
	typedef Vector<int, 5> vec5i;

	typedef Vector<double, 2> vec2d;
	typedef Vector<double, 3> vec3d;
	typedef Vector<double, 4> vec4d;
	typedef Vector<double, 5> vec5d;

	typedef Vector<float, 2> vec2f;
	typedef Vector<float, 3> vec3f;
	typedef Vector<float, 4> vec4f;
	typedef Vector<float, 5> vec5f;
};

#endif
