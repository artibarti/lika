#ifndef LIKA_EXCEPTION_H
#define LIKA_EXCEPTION_H

#include <exception>
#include <iostream>

namespace Lika
{
    class likaConversionException: public std::exception
    {
        virtual const char* what() const throw()
        {
            return "likaConversionException occured";
        }
    };

};

#endif