#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <iostream>
#include <cmath>
#include "matrixexcept.h"

class Matrix
{
public:
    Matrix(int rows, int columns);
    Matrix(double alpha);
    ~Matrix();
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    double& operator()(int i, int j);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix operator*(const Matrix& other) const;

private:
    int rows, columns;
    double** array;
    
    bool isMatrixSizeLegal(const Matrix& other);
    void allocSpace();
    void freeSpace();
};

#endif 