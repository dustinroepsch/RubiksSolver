#ifndef RUBIKS_CUBE_H
#define RUBIKS_CUBE_H

#include <memory>
#include <vector>

enum Side
{
    Front = 0,
    Top,
    Left,
    Right,
    Back,
    Bottom,
    Num_Sides
};
//Color has the same values as side because this is the orientation of the cube at the solved state
//Feels really stupid but I'm too tired to think of a better way to document the solved state
enum Color
{
    White = Front,
    Red = Top,
    Blue = Left,
    Green = Right,
    Yellow = Back,
    Orange = Bottom,
    Num_Colors = Num_Sides
};


class Rubiks_Cube;
typedef std::shared_ptr<Rubiks_Cube> sp_rubiks_cube_t;


class Rubiks_Cube
{
  public:
    Rubiks_Cube(const Color (&state)[Num_Sides][3][3]);

    void print_face(Side face) const;
    void print_cube() const;

    inline bool operator==(const Rubiks_Cube &other) {
        for (int side = 0; side < Num_Sides; side++) {
            for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                    if (this->current_state[side][row][col] != other.current_state[side][row][col]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    /*
    Rotations are clockwise, Prime Rotations are counter clockwise
    */
    sp_rubiks_cube_t rotate_side(Side face) const;
    sp_rubiks_cube_t rotate_sidePrime(Side face) const;

    const static Color solved_state[Num_Sides][3][3]; 

    int solve(int moves[20]); //kill me for that return type

    static bool is_goal(sp_rubiks_cube_t n);

    std::vector<sp_rubiks_cube_t> successors();
    

    private:

    friend class Sub_Problem;
    
    static void rotate_face_counter_clockwise(Color face[3][3]);
    static void rotate_face_clockwise(Color face[3][3]);

    static void transpose_face(Color face[3][3]);

    static void reverse_columns(Color face[3][3]);

    static void copy_state(Color destination[Num_Sides][3][3], const Color (&source)[Num_Sides][3][3]);

    sp_rubiks_cube_t rotateX(Side face) const;
    sp_rubiks_cube_t rotateY(Side face) const;    
    sp_rubiks_cube_t rotateZ(Side face) const;
        

    Color current_state[Num_Sides][3][3];
};

#endif
