#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <iostream>
#include <array>
#include "matrix.h"
#include "matrixexcept.h"

class Vector2
{
public:
    Vector2(int size);
    Vector2(const Vector2& other);
    Vector2& operator=(const Vector2& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);

    

private:
    int size;
    std::array<double, 2> array;
};

#endif