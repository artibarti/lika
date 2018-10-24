#include "../source/lika.hpp"
#include <iostream>

using namespace Lika;

int main(int argc, char** argv)
{
    std::cout << "Lika math library example" << std::endl;

    vec2d v1 {2,5};
    vec2d v2 {4,1};

    vec2d v3 = v1 + v2;

    v2.showInfo();

    mat2x2d m1 
    {
        {2,5},
        {1,5}
    };

    vec2d v4 = m1*v3;
    v4.showInfo();

}