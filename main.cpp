#include <iostream>
#include <Windows.h>
#include "matrix/matrix.h"

void clearScreen() {
    std::system("cls");
}

bool isKeyPressed(char key)
{
    return GetKeyState('A') & 0x8000;
}

constexpr int MAP_SIZE = 15;

int main() {

    Matrix m1(3, 3);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            m1(i, j) = i + j;
        }
    }
    
    std::cout << m1;

    
    return 0;
}
