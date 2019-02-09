
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "lvector.hpp"

namespace Lika
{
    template<typename T, int V, int H>
    class Matrix
    {
        private:
            int size_h = H;
            int size_v = V;
            std::vector<std::vector<T>> values;

        public:
            Matrix();
            Matrix(std::initializer_list<std::initializer_list<T>> il);
            Matrix(T t);

            std::vector<std::vector<T>> getValues() const;
            T get(int row_index, int col_index) const;
            std::vector<T>& operator[] (int index);
            void set(int row_index, int col_index, T t);

            Matrix<T,V,H>& operator=(const Matrix<T,V,H>& m);
            Matrix<T,V,H> operator+(const Matrix<T,V,H>& m);
            Matrix<T,V,H> operator-(const Matrix<T,V,H>& m);

            template<int H_>
            Matrix<T,V,H_> operator*(const Matrix<T,H,H_>& m);            
            Vector<T,V> operator*(const Vector<T,H>& v);

            Matrix<T,H,V> transpose();
            Matrix<T,V,H>& fillWithZeros();
            Matrix<T,V,H>& fillWith(T t);

            void showInfo();
    };

    template<typename T, int V, int H>
    Matrix<T,V,H>::Matrix()
    {
        fillWithZeros();
    }

    template<typename T, int V, int H>
    Matrix<T,V,H>::Matrix(T t)
    {
        fillWith(t);
    }

    template<typename T, int V, int H>
    Matrix<T,V,H>::Matrix(std::initializer_list<std::initializer_list<T>> il)
    {
        if (il.size() == V && 
            std::all_of(il.begin(), il.end(), [](std::initializer_list<T> ile){return ile.size() == H;}))
        {
            values.clear();
            for (auto it = il.begin(); it != il.end(); it++)
            {
                std::vector<T> row_vec;
                std::move(it->begin(), it->end(), std::back_inserter(row_vec));
                values.push_back(row_vec);
            }
        }
		else
			throw std::invalid_argument( "initializer list size does not correspond fot this type" );            
    }

    template<typename T, int V, int H>
    std::vector<std::vector<T>> Matrix<T,V,H>::getValues() const
    {
        return values;
    }

    template<typename T, int V, int H>
    T Matrix<T,V,H>::get(int row_index, int col_index) const
    {
        return values[row_index][col_index];
    }

    template<typename T, int V, int H>
    std::vector<T>& Matrix<T,V,H>::operator[] (int index)
    {
        return values[index];
    }

    template<typename T, int V, int H>
    void Matrix<T,V,H>::set(int row_index, int col_index, T t)
    {
        values[row_index][col_index] = t;
    }

    template<typename T, int V, int H>
    Matrix<T,V,H>& Matrix<T,V,H>::fillWithZeros()
    {
        values.clear();

        for (int rows = 0; rows < size_v; rows++)
        {
            std::vector<T> row_vec;
            for (int cols = 0; cols < size_h; cols++)
            {
                row_vec.push_back(0);
            }
            values.push_back(row_vec);
        }

        return *this;
    }
    
    template<typename T, int V, int H>
    Matrix<T,V,H>& Matrix<T,V,H>::fillWith(T t)
    {
        values.clear();

        for (int rows = 0; rows < size_v; rows++)
        {
            std::vector<T> row_vec;
            for (int cols = 0; cols < size_h; cols++)
            {
                row_vec.push_back(t);
            }
            values.push_back(row_vec);
        }

        return *this;
    }

    template<typename T, int V, int H>
    void Matrix<T,V,H>::showInfo()
    {
        for (int rows = 0; rows<size_v; rows++)
        {
            for (int cols = 0; cols<size_h; cols++)
            {
                std::cout << values[rows][cols] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    template<typename T, int V, int H>
    Matrix<T,V,H>& Matrix<T,V,H>::operator=(const Matrix<T,V,H>& m)
    {
        values.clear;
        std::copy(m.getValues().begin(), m.getValues().end(), std::back_inserter(values));
        return *this;
    }

    template<typename T, int V, int H>
    Matrix<T,V,H> Matrix<T,V,H>::operator+(const Matrix<T,V,H>& m)
    {
        Matrix<T,V,H> result;
        
        for (int row = 0; row < size_v; row++)
        {
            for (int col = 0; col < size_h; col++)
            {
                (result[row])[col] = m.get(row,col) + get(row,col);
            }
        }

        return result;
    }

    template<typename T, int V, int H>
    Matrix<T,V,H> Matrix<T,V,H>::operator-(const Matrix<T,V,H>& m)
    {
        Matrix<T,V,H> result;
        
        for (int row = 0; row < size_v; row++)
        {
            for (int col = 0; col < size_h; col++)
            {
                (result[row])[col] = get(row,col) - m.get(row,col);
            }
        }

        return result;
    }
    
    template<typename T, int V, int H>
    template<int H_>
    Matrix<T,V,H_> Matrix<T,V,H>::operator*(const Matrix<T,H,H_>& m)
    {
        Matrix<T,V,H_> result;

        for(int row_left = 0; row_left<size_v; row_left++)
        {
            for(int col_right = 0; col_right<H_; col_right++)
            {
                T t = 0;
                for (int i = 0; i<size_h; i++)
                {
                    t += values[row_left][i]*m.get(i, col_right);
                }
                result.set(row_left, col_right, t);
            }
        }
        return result;
    }
    
    template<typename T, int V, int H>
    Vector<T,V> Matrix<T,V,H>::operator*(const Vector<T,H>& v)
    {
        Vector<T,V> result;

        for(int row_left = 0; row_left<size_v; row_left++)
        {
            T t = 0;
            for (int col_left = 0; col_left<size_h; col_left++)
            {
                t += values[row_left][col_left]*v.get(col_left);
            }
            result[row_left] = t;
        }
        return result;

    }

    template<typename T, int V, int H>
    Matrix<T,H,V> Matrix<T,V,H>::transpose()
    {
        Matrix<T,H,V> result;
        for(int row = 0; row<size_v; row++)
        {
            for(int col = 0; col<size_h; col++)
            {
                result.set(col, row, values[row][col]);
            }
        }

        return result;
    }

    typedef Matrix<int, 2, 2> mat2x2i;
    typedef Matrix<int, 3, 3> mat3x3i;
    typedef Matrix<int, 4, 4> mat4x4i;

    typedef Matrix<double, 2, 2> mat2x2d;
    typedef Matrix<double, 3, 3> mat3x3d;
    typedef Matrix<double, 4, 4> mat4x4d;

};