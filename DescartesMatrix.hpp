#ifndef DESCARTES_MATRIX_HPP
#define DESCARTES_MATRIX_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "geo.hpp"

class DescartesFunc
{
public:
    virtual void operator()(char& data) const = 0;
};

class PrintFunc : public DescartesFunc
{
public:
    void operator()(char& data) const override {
        std::cout << data << ' ';
    }  
};

class DescartesMatrix
{
public:
    DescartesMatrix(int size) : size(size)
    {
        init_matrix();
    }

    void print_matrix(const DescartesFunc& myF)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                myF(matrix[i][j]);
            }
            std::cout << std::endl;
        }
    }
private:
    const int size;
    std::vector<std::vector<char>> matrix;

    std::vector<Vector2> get_circ_points()
    {
        std::vector<Vector2> points;

        for (int i = 0; i < size; i++)
        {
            float x = 2*(float)i / (size-1) - 1;
            Vector2 point(x, std::sqrt(1 - x*x));
            points.push_back(point);
        }

        return points;
    }

    void init_matrix()
    {
        matrix.resize(size, std::vector<char>(size, '.'));
        
        std::vector<Vector2> points = get_circ_points();
        
        
        for (Vector2 point : points)
        {
            Vector2Des p = point.get_desc_coord(Vector2Des((size-1)/2,(size-1)/2), size);
            matrix[(size-1)/2 - p.y][(size-1)/2 + p.x] = 'X';
        }
    }
    
        
        
};

#endif
