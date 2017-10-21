#ifndef RUBIKS_CUBE_H
#define RUBIKS_CUBE_H

enum Color
{
    Red = 0,
    Blue,
    Yellow,
    Green,
    Orange,
    Black,
    White = Black
};

enum Side
{
    Front,
    Back,
    Left,
    Right,
    Top,
    Bottoms,
    Num_Sides
};

class Rubiks_Cube
{
  public:
    Rubiks_Cube(Color state[Num_Sides][3][3]);
};
#endif