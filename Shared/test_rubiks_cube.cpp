#include "RubiksCube.h"
#include <iostream>

int main()
{
    Color test[Num_Sides][3][3] = {
        {{Red, Yellow, Green},
         {Green, Blue, Yellow},
         {Black, Black, Red}},
        {{Red, Yellow, Green},
         {Green, Blue, Yellow},
         {Black, Black, Red}},
        {{Red, Yellow, Green},
         {Green, Blue, Yellow},
         {Black, Black, Red}},
        {{Red, Yellow, Green},
         {Green, Blue, Yellow},
         {Black, Black, Red}},
        {{Red, Yellow, Green},
         {Green, Blue, Yellow},
         {Black, Black, Red}},
        {{Red, Yellow, Green},
         {Green, Blue, Yellow},
         {Black, Black, Red}}};
    Rubiks_Cube cube(test);
    std::cout << "No Changes:" << std::endl;
    cube.print_face(Front);
    std::cout << std::endl;
    cube.rotate_face_clockwise(cube.current_state[Front]);
    std::cout << "Rotate CLockwise" << std::endl;
    cube.print_face(Front);

    std::cout << "Reverse COlumns:" << std::endl;
    cube.reverse_columns(cube.current_state[Front]);
    std::cout << std::endl;
    cube.print_face(Front);

    cube.rotate_face_counter_clockwise(cube.current_state[Front]);
    std::cout << "Rotate counter CLockwise" << std::endl;
    cube.print_face(Front);

    std::cout << "Transpose:" << std::endl;
    cube.transpose_face(cube.current_state[Front]);
    cube.print_face(Front);

    return 0;
}