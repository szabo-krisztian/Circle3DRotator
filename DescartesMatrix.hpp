#ifndef DESCARTES_MATRIX_HPP
#define DESCARTES_MATRIX_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "Geometry.hpp"

class DescartesMatrix
{
public:
    DescartesMatrix(int size) : size(size), center(geo::Vector2Int((size-1)/2, (size-1)/2)), radius((size-1)/2)
    {
        init_matrix();
    }

    void print_matrix()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                std::cout << matrix[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

private:
    const int size;
    std::vector<std::vector<char>> matrix;
    geo::Vector2Int center;
    int radius;

    void plot_points(std::vector<geo::Vector2Int>& points, int x, int y)
    {
        points.push_back(geo::Vector2Int(center.x + x, center.y + y));
        points.push_back(geo::Vector2Int(center.x - x, center.y + y));
        points.push_back(geo::Vector2Int(center.x + x, center.y - y));
        points.push_back(geo::Vector2Int(center.x - x, center.y - y));
        points.push_back(geo::Vector2Int(center.x + y, center.y + x));
        points.push_back(geo::Vector2Int(center.x - y, center.y + x));
        points.push_back(geo::Vector2Int(center.x + y, center.y - x));
        points.push_back(geo::Vector2Int(center.x - y, center.y - x));
    }

    std::vector<geo::Vector2Int> get_circle_points()
    {
        int x = radius;
        int y = 0;
        int p = 1 - radius;

        std::vector<geo::Vector2Int> points;
        while (x >= y)
        {
            plot_points(points, x, y);
            y++;
            if (p <= 0)
            {
                p = p + 2 * y + 1;
            }
            else
            {
                x--;
                p = p + 2 * y - 2 * x + 1;
            }
        }

        return points;
    }

    void init_matrix()
    {
        matrix.resize(size, std::vector<char>(size, '.'));
        auto points = get_circle_points();
        for (const auto& i : points)
        {
            std::cout << i.x - center.x << ',' << i.y - center.y << std::endl;
            matrix[i.y][i.x] = '#';
        }
        print_matrix();
    }
    
    //std::vector<geo::Vector2Int> get_rotated_points(const std::vector<geo::Vector2Int>& points, )
};

#endif
