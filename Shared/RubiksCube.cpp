#include "RubiksCube.h"
#include <iostream>

Rubiks_Cube::Rubiks_Cube(const Color (&state)[Num_Sides][3][3]) {
    for (int side = 0; side < Num_Sides; side++) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                current_state[side][row][col] = state[side][row][col];
            }
        }
    }
}

void Rubiks_Cube::print_face(Side face) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            std::cout << current_state[face][row][col] << " ";
        }
        std::cout << std::endl;
    }
}


void Rubiks_Cube::transpose_face(Color face[3][3]) {
    Color stupid_copy[3][3];
    std::cout << "this is happening" << std::endl;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            stupid_copy[row][col] = face[col][row];
        }
    }
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            face[row][col] = stupid_copy[row][col];
        }
    }
}

void Rubiks_Cube::reverse_columns(Color face[3][3]) {
    for (int row = 0; row < 3; row++) {
        Color temp = face[row][0];
        face[row][0] = face[row][2];
        face[row][2] = temp;
    }
}

void Rubiks_Cube::rotate_face_clockwise(Color face[3][3]) {
    transpose_face(face);
    reverse_columns(face);
}

void Rubiks_Cube::rotate_face_counter_clockwise(Color face[3][3]) {
    //it's a hackathon give me a break
    for (int i = 0; i < 3; i++) {
        rotate_face_clockwise(face);
    }
    
}

