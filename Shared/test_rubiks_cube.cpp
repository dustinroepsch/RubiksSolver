#include "RubiksCube.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    Color input[Num_Colors][3][3] = {
        {
            {Blue, Yellow, Orange},
            {Blue, White, Green},
            {Red, White, Orange}
        },
        {
            {Green, Green, Orange},
            {Yellow, Red, Orange},
            {Yellow, Green, Green}            
        },
        {
            {White, Orange, Orange},
            {Red, Blue, Red},
            {White, White, Green}
        },
        {
            {Yellow, White, Green},
            {White, Green, Green},
            {Blue, Yellow, Yellow}
        },
        {
            {White, Red, Red},
            {Orange, Yellow, Yellow},
            {Red, Blue, Red}
        },
        {
            {Yellow, Red, White},
            {Blue, Orange, Blue},
            {Blue, Orange, Blue}            
        }
    };
    //front up front right bottom left bottom back
    sp_rubiks_cube_t cube = std::make_shared<Rubiks_Cube>(input);
    cube->print_cube();
    int path[20];
    int solutions = cube->solve(path);
    for (int i = 0; i < solutions; i++){
        std::cout << path[i] << std::endl;
    }   

    
    return 0;
}