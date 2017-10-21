#include "RubiksCube.h"
#include <iostream>

int main()
{
    sp_rubiks_cube_t cube = std::make_shared<Rubiks_Cube>(Rubiks_Cube::solved_state);
    std::cout << "Start:" << std::endl;
    cube->print_cube();

    std::cout << "Turn Front:" << std::endl;
    cube = cube->rotate_side(Front);
    cube->print_cube();
    std::cout << "Turn Right:" << std::endl;
    cube = cube->rotate_side(Right);
    cube->print_cube();
    return 0;
}