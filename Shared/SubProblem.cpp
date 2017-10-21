#include "SubProblem.h"

#include "RubiksCube.h"

bool only_red_white_or_blue(Color a, Color b, Color c) {
    return (a == Red || a == White || a == Blue) &&
           (b == Red || b == White || b == Blue) &&
           (c == Red || c == White || c == Blue) &&
}

Sub_Problem::Sub_Problem(const Color (&large_problem)[Num_Sides][3][3]) {
    sp_rubiks_cube_t cube = std::make_shared<Rubiks_Cube>(large_problem);

    int z, x, y;

    //check bottom half of cube
   
    bool need_to_flip_cube_upside_down = false;

     //front left bottom
    if (only_red_white_or_blue(cube->current_state[Front][2][0], cube->current_state[Left][2][2], cube->current_state[Bottom][0][0])) {
        need_to_flip_cube_upside_down = true;
    }
    //front right bottom
    if (only_red_white_or_blue(cube->current_state[Front][2][2], cube->current_state[Right][2][0], cube->current_state[Bottom][0][2])) {
        need_to_flip_cube_upside_down = true;
    }

    //back right bottom
    if (only_red_white_or_blue(cube->current_state[Back][2][0], cube->current_state[Right][2][2], cube->current_state[Bottom][2][2])) {
        need_to_flip_cube_upside_down = true;
    }

    //back left bottom
    if (only_red_white_or_blue(cube->current_state[Back][2][2], cube->current_state[Left][2][0], cube->current_state[Bottom][2][0])) {
        need_to_flip_cube_upside_down = true;
    }

    if (need_to_flip_cube_upside_down) {
        cube = cube->rotate_side(Right)->rotate_side(Right)->rotate_sidePrime(Left)->rotate_sidePrime(Left);
    }

    while(!only_red_white_or_blue(cube->current_state[Front][0][0], cube->current_state[Left][0][2], cube->current_state[Top][2][0])) {
        cube = cube->rotate_side(Top)->rotate_side(Top)->rotate_sidePrime(Bottom)->rotate_sidePrime(Bottom);
    }

    while(cube->current_state[Top][2][0] != Red) {
        cube = cube->rotate_side(Left)->rotate_side(Left)->rotate_sidePrime(Right)->rotate_sidePrime(Right);
        cube = cube->rotate_side(Front)->rotate_side(Front)->rotate_sidePrime(Back)->rotate_sidePrime(Back);
    }

    for (int side = i; i < Num_Sides; i++) {
        colors[side][0][0] = cube->current_state[side][0][0];
        colors[side][0][1] = cube->current_state[side][0][2];
        colors[side][1][0] = cube->current_state[side][2][0];
        colors[side][1][1] = cube->current_state[side][2][2];
    }


}