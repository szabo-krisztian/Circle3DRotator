#include "vector2.h"

Vector2::Vector2(int size) : size(size)
{
    array.fill(0);
}

Vector2::Vector2(const Vector2& other) : size(other.size)
{
    array = other.array;
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    size = rhs.size;
    array = rhs.array;
}

std::ostream& operator<<(std::ostream& os, const Vector2& vector)
{
    for (const auto& element : vector.array)
    {
        os << element << ' ';
    }
    os << std::endl;
}