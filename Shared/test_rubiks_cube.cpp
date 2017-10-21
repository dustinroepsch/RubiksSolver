#include "RubiksCube.h"
#include <iostream>

int main()
{
    //front up front right bottom left bottom back
    sp_rubiks_cube_t cube = std::make_shared<Rubiks_Cube>(Rubiks_Cube::solved_state);
    std::cout << "Start:" << std::endl;
    cube->print_cube();

    std::cout << "Turn Front:" << std::endl;
    cube = cube->rotate_side(Front);
    cube->print_cube();
    std::cout << "Turn Top:" << std::endl;
    cube = cube->rotate_side(Top);
    cube->print_cube();
    std::cout << "Turn Front:" << std::endl;
    cube = cube->rotate_side(Front);
    cube->print_cube();
    std::cout << "Turn Right:" << std::endl;
    cube = cube->rotate_side(Right);
    cube->print_cube();
    std::cout << "Turn Bottom:" << std::endl;
    cube = cube->rotate_side(Bottom);
    cube->print_cube();
    std::cout << "Turn Left:" << std::endl;
    cube = cube->rotate_side(Left);
    cube->print_cube();
    std::cout << "Turn Bottom:" << std::endl;
    cube = cube->rotate_side(Bottom);
    cube->print_cube();
    std::cout << "Turn Back:" << std::endl;
    cube = cube->rotate_side(Back);
    cube->print_cube();
    return 0;
}