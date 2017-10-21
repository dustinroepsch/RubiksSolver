#ifndef RUBIKS_CUBE_H
#define RUBIKS_CUBE_H

#include <memory>

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
    Bottom,
    Num_Sides
};
class Rubiks_Cube;
typedef std::shared_ptr<Rubiks_Cube> sp_rubiks_cube_t;

class Rubiks_Cube
{
  public:
    Rubiks_Cube(const Color (&state)[Num_Sides][3][3]);

    void print_face(Side face);

    /*
    Rotations are clockwise, Prime Rotations are counter clockwise
    */
    sp_rubiks_cube_t rotate_side(Side face) const;
    //sp_rubiks_cube_t rotate_sidePrime(Side face) const;

    //  private:
    static void rotate_face_counter_clockwise(Color face[3][3]);
    static void rotate_face_clockwise(Color face[3][3]);

    static void transpose_face(Color face[3][3]);

    static void reverse_columns(Color face[3][3]);

    static void copy_state(Color destination[Num_Sides][3][3], const Color (&source)[Num_Sides][3][3]);

    sp_rubiks_cube_t rotateX(Side face) const;
        

    Color current_state[Num_Sides][3][3];
};

#endif