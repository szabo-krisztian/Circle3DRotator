#include <iostream>
#include <vector>
#include <cmath>
#include "matrix/matrix.h"

constexpr int PICTURE_SIZE = 23;
constexpr int CENTER = (PICTURE_SIZE - 1) / 2;
constexpr int RADIUS = CENTER;
constexpr double ANGLE = M_PI / 4;

Matrix create_2d_vector(double x, double y)
{
    Matrix vector(2, 1);
    vector(0, 0) = x;
    vector(1, 0) = y;
    return vector;
}

void plot_points(std::vector<Matrix>& points, int x, int y)
{
    points.push_back(create_2d_vector(CENTER + x, CENTER + y));
    points.push_back(create_2d_vector(CENTER + x, CENTER + y));
    points.push_back(create_2d_vector(CENTER - x, CENTER + y));
    points.push_back(create_2d_vector(CENTER + x, CENTER - y));
    points.push_back(create_2d_vector(CENTER - x, CENTER - y));
    points.push_back(create_2d_vector(CENTER + y, CENTER + x));
    points.push_back(create_2d_vector(CENTER - y, CENTER + x));
    points.push_back(create_2d_vector(CENTER + y, CENTER - x));
    points.push_back(create_2d_vector(CENTER - y, CENTER - x));
}

std::vector<Matrix> get_circle_points()
{
    int x = RADIUS;
    int y = 0;
    int p = 1 - RADIUS;

    std::vector<Matrix> points;
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

void print_pic_matrix(const std::vector<std::vector<char>>& picture)
{
    for (int i = 0; i < PICTURE_SIZE; ++i)
    {
        for (int j = 0; j < PICTURE_SIZE; ++j)
        {
            std::cout << picture[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

Matrix get_cartesian_coord(Matrix& plane_coord)
{
    Matrix cartesian(3, 1);
    cartesian(0, 0) = plane_coord(0, 0) - CENTER;
    cartesian(1, 0) = plane_coord(1, 0) - CENTER;
    cartesian(2, 0) = 0;
    return cartesian;
}

Matrix get_plane_coord(Matrix& cartesian_coord)
{
    Matrix plane_coord(2, 1);
    plane_coord(0, 0) = (int)round(cartesian_coord(0, 0)) + CENTER;
    plane_coord(1, 0) = (int)round(cartesian_coord(1, 0)) + CENTER;
    return plane_coord;
}

Matrix create_x_rotation_matrix(double angle)
{
    Matrix rotation(3, 3);
    double sinAngle = std::sin(angle);
    double cosAngle = std::cos(angle);

    rotation(1, 1) = 1;
    rotation(0, 0) = cosAngle;
    rotation(0, 2) = sinAngle;
    rotation(2, 0) = -sinAngle;
    rotation(2, 2) = cosAngle;
    return rotation;
}

void clear_picture(std::vector<std::vector<char>>& picture)
{
    for (int i = 0; i < PICTURE_SIZE; ++i)
    {
        for (int j = 0; j < PICTURE_SIZE; ++j)
        {
            picture[i][j] = '.';
        }
    }
}

void rotate(double angle, std::vector<Matrix>& points, std::vector<std::vector<char>>& picture)
{
    points = get_circle_points();

    for (auto& p : points)
    {
        Matrix homo_coord = get_cartesian_coord(p);

        std::cout << "start: " << homo_coord << std::endl;

        Matrix rotation = create_x_rotation_matrix(angle);
        p = rotation * homo_coord;
        std::cout << "end: " << p << std::endl;
    }
    
    clear_picture(picture);
    for (auto& p : points)
    {
        auto plane_coord = get_plane_coord(p);
        picture[plane_coord(0, 0)][plane_coord(1, 0)] = '#';
    }

    print_pic_matrix(picture);
}

int main()
{
    std::vector<std::vector<char>> picture;
    picture.resize(PICTURE_SIZE, std::vector<char>(PICTURE_SIZE, '.'));

    auto points = get_circle_points();
    for (auto& p : points)
    {
        picture[(int)p(0, 0)][(int)p(1, 0)] = '#';
    }


    for (int i = 0;i < 10; ++i)
    {
        int degree;
        std::cout << "enter degree: ";
        std::cin >> degree;
        double angle = degree * (M_PI / 180.0);
        rotate(angle, points, picture);
    }    

    return 0;
}
