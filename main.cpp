#include <iostream>
#include <Windows.h>
#include "matrix/matrix.h"
#include "geo.hpp"
#include <cmath>

int main()
{
    Matrix vec1(2,1);
    vec1(0,0) = 1;
    vec1(1,0) = 0;
    
    Matrix rotat(2,2);
    double cosAngle = std::cos(M_PI / 3);
    double sinAngle = std::sin(M_PI / 3);
    rotat(0,0) = cosAngle;
    rotat(0,1) = -sinAngle;
    rotat(1,0) = sinAngle;
    rotat(1,1) = cosAngle;

    auto res = rotat *= vec1;
    std::cout << res;

    return 0;
}
