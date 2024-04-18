#ifndef GEO_HPP
#define GEP_HPP

#include <iostream>
#include <cmath>

class Vector2Des
{
public:
    int x, y;
    Vector2Des(int x, int y) : x(x), y(y) { }

    friend std::ostream& operator<<(std::ostream& os, const Vector2Des& obj)
    {
        os << "(" << obj.x << ", " << obj.y << ')' << std::endl;
        return os;
    }
};

class Vector2
{
public:
    float x, y;

    Vector2(float x, float y) : x(x), y(y) { }
    Vector2Des get_desc_coord(const Vector2Des& origo, int size)
    {
        return Vector2Des(x * origo.x,y * origo.x);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& obj)
    {
        os << "(" << obj.x << ", " << obj.y << ')' << std::endl;
        return os;
    }
};



#endif 