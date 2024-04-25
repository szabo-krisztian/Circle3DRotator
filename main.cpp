#include <iostream>
#include <vector>
#include <Windows.h>
#include <cmath>
#include "matrix/matrix.h"

const int PICTURE_SIZE = 21;

std::vector<Matrix> get_circle_points()
{
    
}

int main()
{
    Matrix vec(2,1);
    double alpha = M_PI / 3;
    Matrix rotatMatrix(alpha);
    Matrix res = rotatMatrix * vec;
    std::cout << res;

    return 0;
}
