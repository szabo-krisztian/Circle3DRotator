#ifndef __MATRIXEXCEPT_H__
#define __MATRIXEXCEPT_H__

#include <stdexcept>

class MatrixSizeException : public std::exception
{
public:
    virtual const char* what() noexcept
    {
        return "Illegal matrix size";
    }
};

class IndexOutOfRangeException : public std::exception
{
public:
    virtual const char* what() noexcept
    {
        return "Index out of range";
    }
};

#endif