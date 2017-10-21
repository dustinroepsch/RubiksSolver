#include "RubiksCube.h"
#include <iostream>

int main()
{
    Rubiks_Cube cube(Rubiks_Cube::solved_state);
    std::cout << "Before turn" << std::endl;
    cube.print_cube();

    std::cout << "After Turn" << std::endl;
    cube.rotate_side(Front)->print_cube();
    cube.print_cube();
    return 0;
}