#ifndef LIKA_CONVERSION_H
#define LIKA_CONVERSION_H

#include "lvector.hpp"
#include "lexception.hpp"
#include <vector>

namespace Lika 
{
    template<typename T, int S>
    Vector<T,S+1> addPolarCoordinates(const Vector<T,S>& v)
    {
        Vector<T,S+1> result;
        
        std::vector<T> result_values = v.getValues();
        result_values.push_back(1);

        result.setValues(result_values);
        return result;
    }

    template<typename T, int S>
    Vector<T,S+1> removePolarCoordinates(const Vector<T,S>& v)
    {
        if (S < 2)
            throw likaConversionException("can not remove dimension from a 1 dimension vector");

        Vector<T,S-1> result;
        
        std::vector<T> result_values = v.getValues();
        result_values.erase(result_values.end());

        result.setValues(result_values);
        return result;
    }

    template<typename T, int S>
    std::vector<Vector<T,S+1>> addPolarCoordinates(const std::vector<Vector<T,S>>& vectors)
    {
        std::vector<Vector<T,S+1>> result;
        
        for (int i = 0; i<vectors.size(); i++)
        {
            Vector<T,S+1> new_vector;
            
            std::vector<T> new_vector_result_values = vectors[i].getValues();            
            new_vector_result_values.push_back(1);

            new_vector.setValues(new_vector_result_values);
            result.push_back(new_vector);
        }

        return result;
    }

    template<typename T, int S>
    std::vector<Vector<T,S-1>> removePolarCoordinates(const std::vector<Vector<T,S>>& vectors)
    {
        if (S < 2)
            throw likaConversionException("can not remove dimension from a 1 dimension vector");

        std::vector<Vector<T,S+1>> result;
        
        for (int i = 0; i<vectors.size(); i++)
        {
            Vector<T,S+1> new_vector;
            
            std::vector<T> new_vector_result_values = vectors[i].getValues();            
            new_vector_result_values.erase(new_vector_result_values.end());

            new_vector.setValues(new_vector_result_values);
            result.push_back(new_vector);
        }

        return result;
    }

};

#endif