#include "RubiksCube.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    //front up front right bottom left bottom back
    sp_rubiks_cube_t cube = std::make_shared<Rubiks_Cube>(Rubiks_Cube::solved_state);
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        int side = rand() % Num_Sides;
        bool clockwise = rand() % 2;
        if (clockwise) {
            cube = cube->rotate_side(Side(side));
        } else {
            cube = cube->rotate_sidePrime(Side(side));
        }
    }

    std::shared_ptr<std::vector<std::string>> solutions = cube->solve();
    for (std::string str : *solutions ){
        std::cout << str << std::endl;
    }   
    return 0;
}