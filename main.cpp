#include <iostream>
#include <Windows.h>
#include "DescartesMatrix.hpp"

void clearScreen() {
    std::system("cls");
}

bool isKeyPressed(char key)
{
    return GetKeyState('A') & 0x8000;
}

constexpr int MAP_SIZE = 15;

int main() {
    bool running = true;
    DescartesMatrix matrix(23);

    matrix.print_matrix(PrintFunc());

    /*
    while (running) {
        clearScreen();
        
    


        if (isKeyPressed('A'))
        {
            running = false;
        }
    }
    */

    return 0;
}
