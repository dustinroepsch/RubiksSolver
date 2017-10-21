#include "RubiksCube.h"

int main() {
    Side degrees_of_freedom[] = {Bottom, Right, Back};
    sp_rubiks_cube_t cube = std::make_shared<Rubiks_Cube>(Rubiks_Cube::solved_state);
    

    return 0;
}