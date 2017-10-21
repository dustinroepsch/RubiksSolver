#include "RubiksCube.h"
#include <iostream>
#include <cassert>

const Color Rubiks_Cube::solved_state[Num_Sides][3][3] = {
    {{White, White, White},
     {White, White, White},
     {White, White, White}},
    {{Red, Red, Red},
     {Red, Red, Red},
     {Red, Red, Red}},
    {{Blue, Blue, Blue},
     {Blue, Blue, Blue},
     {Blue, Blue, Blue}},
    {{Green, Green, Green},
     {Green, Green, Green},
     {Green, Green, Green}},
    {{Black, Black, Black},
     {Black, Black, Black},
     {Black, Black, Black}},
    {{Yellow, Yellow, Yellow},
     {Yellow, Yellow, Yellow},
     {Yellow, Yellow, Yellow}},
};

Rubiks_Cube::Rubiks_Cube(const Color (&state)[Num_Sides][3][3])
{
    copy_state(current_state, state);
}

void Rubiks_Cube::print_face(Side face) const
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            std::cout << current_state[face][row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Rubiks_Cube::transpose_face(Color face[3][3])
{
    Color stupid_copy[3][3];
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            stupid_copy[row][col] = face[col][row];
        }
    }
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            face[row][col] = stupid_copy[row][col];
        }
    }
}

void Rubiks_Cube::reverse_columns(Color face[3][3])
{
    for (int row = 0; row < 3; row++)
    {
        Color temp = face[row][0];
        face[row][0] = face[row][2];
        face[row][2] = temp;
    }
}

void Rubiks_Cube::rotate_face_clockwise(Color face[3][3])
{
    transpose_face(face);
    reverse_columns(face);
}

void Rubiks_Cube::rotate_face_counter_clockwise(Color face[3][3])
{
    //it's a hackathon give me a break
    for (int i = 0; i < 3; i++)
    {
        rotate_face_clockwise(face);
    }
}

void Rubiks_Cube::copy_state(Color destination[Num_Sides][3][3], const Color (&source)[Num_Sides][3][3])
{
    for (int side = 0; side < Num_Sides; side++)
    {
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                destination[side][row][col] = source[side][row][col];
            }
        }
    }
}

sp_rubiks_cube_t Rubiks_Cube::rotateX(Side face) const
{
    assert(face == Front || face == Back);

    Color next_state[Num_Sides][3][3];

    copy_state(next_state, current_state);
    rotate_face_clockwise(next_state[face]);

    int index = face == Front ? 0 : 2;

    //right side
    for (int i = 0; i < 3; i++)
    {
        next_state[Right][i][index] = current_state[Top][2 - index][i];
    }

    //top side
    for (int i = 0; i < 3; i++)
    {
        next_state[Top][2 - index][i] = current_state[Left][2 - i][2 - index];
    }

    //left side
    for (int i = 0; i < 3; i++)
    {
        next_state[Left][2 - i][2 - index] = current_state[Bottom][index][2 - i];
    }
    //bottom side
    for (int i = 0; i < 3; i++)
    {
        next_state[Bottom][index][2 - i] = current_state[Right][i][index];
    }
    return std::make_shared<Rubiks_Cube>(next_state);
}

sp_rubiks_cube_t Rubiks_Cube::rotateY(Side face) const
{
    assert(face == Right || face == Left);

    Color next_state[Num_Sides][3][3];

    copy_state(next_state, current_state);
    rotate_face_clockwise(next_state[face]);

    int index = face == Right ? 0 : 2;

    //top side
    for (int i = 0; i < 3; i++) {
        next_state[Top][2 - i][2 - index] = current_state[Front][2 - i][2 - index];
    }

    //back
    for (int i = 0; i < 3; i++) {
        next_state[Back][i][index] =  current_state[Top][2 - i][2 - index];        
    }


    //bottom
    for (int i = 0; i < 3; i++) {
       next_state[Bottom][i][2 - index] = current_state[Back][2-i][index];    
    }

    //front
    for (int i = 0; i < 3; i++) {
        next_state[Front][2 - i][2 - index] = current_state[Bottom][2-i][2 - index];        
    }

    return std::make_shared<Rubiks_Cube>(next_state);
}

void Rubiks_Cube::print_cube() const
{
    std::cout << "Front" << std::endl;
    print_face(Front);

    std::cout << "Left" << std::endl;
    print_face(Left);

    std::cout << "Right" << std::endl;
    print_face(Right);

    std::cout << "Top" << std::endl;
    print_face(Top);

    std::cout << "Bottom" << std::endl;
    print_face(Bottom);

    std::cout << "Back" << std::endl;
    print_face(Back);
}

sp_rubiks_cube_t Rubiks_Cube::rotate_side(Side face) const
{
    switch (face)
    {
    case Front:
    case Back:
        return rotateX(face);
    case Left:
    case Right:
        return rotateY(face);
        break;
    case Top:
    case Bottom:
        break;
    default:
        assert(false);
    }
    std::cout << "Bad things are happening" << std::endl;
    return std::make_shared<Rubiks_Cube>(solved_state);
}
