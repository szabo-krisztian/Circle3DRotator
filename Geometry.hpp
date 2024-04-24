#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include <iostream>
#include <vector>

namespace geo
{
    class Vector2Int
    {
    public:
        int x, y;
        
        Vector2Int(int x, int y) : x(x), y(y) {}

        friend std::ostream& operator<<(std::ostream& os, const Vector2Int& obj)
        {
            os << '(' << obj.x << ',' << obj.y << ')';
        }
    };
}

#endif