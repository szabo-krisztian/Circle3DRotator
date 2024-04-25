#include "matrix.h"

Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns)
{
    allocSpace();
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            array[i][j] = 0;
        }
    }
}

Matrix::Matrix(double alpha) : rows(2), columns(2)
{
    allocSpace();
    double cosAngle = std::cos(alpha);
    double sinAngle = std::sin(alpha);

    (*this)(0,0) = cosAngle;
    (*this)(0,1) = sinAngle;
    (*this)(1,0) = -sinAngle;
    (*this)(1,1) = cosAngle;
}

Matrix::~Matrix()
{
    freeSpace();
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), columns(other.columns)
{
    allocSpace();
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            array[i][j] = other.array[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    
    bool isMatrixSizeLegal = rows == rhs.rows && columns == rhs.columns;
    if (!isMatrixSizeLegal)
    {
        freeSpace();
        rows = rhs.rows;
        columns = rhs.columns;
        allocSpace();
    }
    
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            array[i][j] = rhs.array[i][j];
        }
    }

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    for (int i = 0; i < matrix.rows; ++i)
    {
        for (int j = 0; j < matrix.columns; ++j)
        {
            os << matrix.array[i][j] << ' ';
        }
        os << std::endl;
    }
}



double& Matrix::operator()(int i, int j)
{
    bool isLegalIndexes = i < rows && j < columns;
    if (!isLegalIndexes)
    {
        throw IndexOutOfRangeException();
    }

    return array[i][j];
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    bool isMatrixSizeLegal = other.rows == rows && other.columns == columns;
    if (!isMatrixSizeLegal)
    {
        throw MatrixSizeException();
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            array[i][j] += other.array[i][j];
        }
    }

    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    bool isMatrixSizeLegal = other.rows == rows && other.columns == columns;
    if (!isMatrixSizeLegal)
    {
        throw MatrixSizeException();
    }

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            array[i][j] -= other.array[i][j];
        }
    }

    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    bool isMatrixSizeLegal = columns == other.rows;
    if (!isMatrixSizeLegal)
    {
        throw MatrixSizeException();
    }

    Matrix temp(rows, other.columns);
    for (int i = 0; i < temp.rows; ++i) {
        for (int j = 0; j < temp.columns; ++j) {
            for (int k = 0; k < columns; ++k) {
                
                temp.array[i][j] += (array[i][k] * other.array[k][j]);
            }
        }
    }
    
    
    *this = temp;
    return *this;
}

Matrix Matrix::operator*(const Matrix& other) const
{
    bool isMatrixSizeLegal = columns == other.rows;
    if (!isMatrixSizeLegal)
    {
        std::cout << "sad";
        throw MatrixSizeException();
    }

    Matrix result(*this);
    result *= other;
    return result;
}



void Matrix::allocSpace()
{
    array = new double*[rows];
    for (int i = 0; i < rows; ++i)
    {
        array[i] = new double[columns];
    }
}

void Matrix::freeSpace()
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] array[i];
    }
    delete[] array;
}