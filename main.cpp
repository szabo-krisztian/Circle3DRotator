#include <iostream>
#include <vector>
#include <cmath>
#include <Windows.h>
#include "matrix/matrix.h"

constexpr int ANGLE_DEGREE = 10;
constexpr double ANGLE_RADIAN = ANGLE_DEGREE * (M_PI / 180.0);


Matrix create_3d_vector(double x, double y)
{
    Matrix vector(3, 1);
    vector(0, 0) = x;
    vector(1, 0) = y;
    vector(2, 0) = 0;
    return vector;
}

std::vector<Matrix> get_circle_plane_vectors(int radius, int center)
{
    int x = radius;
    int y = 0;
    int p = 1 - radius;

    std::vector<Matrix> points;
    while (x >= y)
    {
        points.push_back(create_3d_vector(center + x, center + y));
        points.push_back(create_3d_vector(center + x, center + y));
        points.push_back(create_3d_vector(center - x, center + y));
        points.push_back(create_3d_vector(center + x, center - y));
        points.push_back(create_3d_vector(center - x, center - y));
        points.push_back(create_3d_vector(center + y, center + x));
        points.push_back(create_3d_vector(center - y, center + x));
        points.push_back(create_3d_vector(center + y, center - x));
        points.push_back(create_3d_vector(center - y, center - x));

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

void print_picture(const std::vector<std::vector<char>>& picture)
{
    for (int i = 0; i < picture.size(); ++i)
    {
        for (int j = 0; j < picture.size(); ++j)
        {
            std::cout << picture[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

Matrix get_cartesian_coord(Matrix& plane_coord, int center)
{
    Matrix cartesian(3, 1);
    cartesian(0, 0) = plane_coord(0, 0) - center;
    cartesian(1, 0) = plane_coord(1, 0) - center;
    cartesian(2, 0) = 0;
    return cartesian;
}

Matrix get_plane_coord(Matrix& cartesian_coord, int center)
{
    Matrix plane_coord(2, 1);
    plane_coord(0, 0) = static_cast<int>(std::round(cartesian_coord(0, 0))) + center;
    plane_coord(1, 0) = static_cast<int>(std::round(cartesian_coord(1, 0))) + center;
    return plane_coord;
}

void clear_picture(std::vector<std::vector<char>>& picture)
{
    for (int i = 0; i < picture.size(); ++i)
    {
        for (int j = 0; j < picture.size(); ++j)
        {
            picture[i][j] = '.';
        }
    }
}

void clear_screen() {
    std::system("cls");
}

bool is_key_pressed(char key)
{
    return GetKeyState(key) & 0x8000;
}

bool plane_coord_in_picture(Matrix& plane_coord, int pic_size)
{
    return plane_coord(0, 0) >= 0 && plane_coord(0, 0) < pic_size && plane_coord(1, 0) >= 0 && plane_coord(1, 0) < pic_size;
}

void set_picture(std::vector<Matrix>& cartesian_points, std::vector<std::vector<char>>& picture, int center)
{
    for (auto& p : cartesian_points)
    {
        Matrix plane_coord = get_plane_coord(p, center);
        picture[plane_coord(1, 0)][plane_coord(0, 0)] = '#';
    }
  
}

void rotate(Matrix& rotation, std::vector<Matrix>& cartesian_points, std::vector<std::vector<char>>& picture, int center)
{
    clear_picture(picture);
    for (auto& p : cartesian_points)
    {
        p = rotation * p;
    }
    set_picture(cartesian_points, picture, center);
    print_picture(picture);
}

int main()
{
    Matrix rotationX = Matrix::get_x_rotation(ANGLE_RADIAN);
    Matrix rotationY = Matrix::get_y_rotation(ANGLE_RADIAN);
    Matrix rotationZ = Matrix::get_z_rotation(ANGLE_RADIAN);
    
    std::vector<std::vector<char>> picture;
    int radius;
    std::cout << "Enter circle radius: ";
    std::cin >> radius;

    int size = 2 * radius + 1;
    int center = radius;
    
    picture.resize(size, std::vector<char>(size, '.'));

    std::vector<Matrix> cartesian_points = get_circle_plane_vectors(radius, center);
    for (auto& p : cartesian_points)
    {
        p = get_cartesian_coord(p, center);
    }

    set_picture(cartesian_points, picture, center);
    print_picture(picture);

    bool isXPressed = false;
    bool isYPressed = false;
    bool isZPressed = false;

    bool running = true;
    while (running)
    {
        if (is_key_pressed('X') && !isXPressed)
        {
            rotate(rotationX, cartesian_points, picture, center);
            isXPressed = true;
        }
        else if (!is_key_pressed('X'))
        {
            isXPressed = false;
        }
        
        if (is_key_pressed('Y') && !isYPressed)
        {
            rotate(rotationY, cartesian_points, picture, center);
            isYPressed = true;
        }
        else if (!is_key_pressed('Y'))
        {
            isYPressed = false;
        }

        if (is_key_pressed('Z') && !isZPressed)
        {
            rotate(rotationZ, cartesian_points, picture, center);
            isZPressed = true;
        }
        else if (!is_key_pressed('Z'))
        {
            isZPressed = false;
        }

        if (is_key_pressed(VK_ESCAPE))
        {
            running = false;
        }
    }
    
    return 0;
}
