#include "RubiksCube.h"
#include <iostream>
#include <cassert>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <deque>
#include <climits>
#include "SubProblem.h"

#define FOUND -2
#define N0T_FOUND -1

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
    {{Yellow, Yellow, Yellow},
     {Yellow, Yellow, Yellow},
     {Yellow, Yellow, Yellow}},
    {{Orange, Orange, Orange},
     {Orange, Orange, Orange},
     {Orange, Orange, Orange}},
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
    if (face == Front)
    {
        rotate_face_clockwise(next_state[face]);
    }
    else
    {
        rotate_face_counter_clockwise(next_state[face]);
    }

    int index = face == Front ? 0 : 2;
    for (int j = 0; j <= index; j++) //far way side needs to rotate 3 times to be clockwise;
    {

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
    }
    return std::make_shared<Rubiks_Cube>(next_state);
}

sp_rubiks_cube_t Rubiks_Cube::rotateY(Side face) const
{
    assert(face == Right || face == Left);

    Color next_state[Num_Sides][3][3];

    copy_state(next_state, current_state);

    if (face == Right)
    {
        rotate_face_clockwise(next_state[face]);
    }
    else
    {
        rotate_face_counter_clockwise(next_state[face]);
    }

    int index = face == Right ? 0 : 2;

    for (int j = 0; j <= index; j++)
    { //far away side needs to rotate 3 times to be clockwise

        //top side
        for (int i = 0; i < 3; i++)
        {
            next_state[Top][2 - i][2 - index] = current_state[Front][2 - i][2 - index];
        }

        //back
        for (int i = 0; i < 3; i++)
        {
            next_state[Back][i][index] = current_state[Top][2 - i][2 - index];
        }

        //bottom
        for (int i = 0; i < 3; i++)
        {
            next_state[Bottom][i][2 - index] = current_state[Back][2 - i][index];
        }

        //front
        for (int i = 0; i < 3; i++)
        {
            next_state[Front][2 - i][2 - index] = current_state[Bottom][2 - i][2 - index];
        }
    }

    return std::make_shared<Rubiks_Cube>(next_state);
}
sp_rubiks_cube_t Rubiks_Cube::rotateZ(Side face) const
{
    assert(face == Top || face == Bottom);
    Color next_state[Num_Sides][3][3];

    copy_state(next_state, current_state);
    int index = face == Top ? 0 : 2;
    if (face == Top)
    {
        rotate_face_clockwise(next_state[face]);
    }
    else
    {
        rotate_face_counter_clockwise(next_state[face]);
    }

    //back
    for (int i = 0; i < 3; i++)
    {
        next_state[Back][index][i] = current_state[Left][index][i];
    }

    //right
    for (int i = 0; i < 3; i++)
    {
        next_state[Right][index][i] = current_state[Back][index][i];
    }

    //Front
    for (int i = 0; i < 3; i++)
    {
        next_state[Front][index][i] = current_state[Right][index][i];
    }

    //left
    for (int i = 0; i < 3; i++)
    {
        next_state[Left][index][i] = current_state[Front][index][i];
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
        return rotateX(face);
    case Back:
        return rotateX(face)->rotateX(face)->rotateX(face);
    case Right:
        return rotateY(face);
    case Left:
        return rotateY(face)->rotateY(face)->rotateY(face);
    case Top:
        return rotateZ(face);
    case Bottom:
        return rotateZ(face)->rotateZ(face)->rotateZ(face);
        break;
    default:
        assert(false);
    }
    std::cout << "Bad things are happening" << std::endl;
    return std::make_shared<Rubiks_Cube>(solved_state);
}

sp_rubiks_cube_t Rubiks_Cube::rotate_sidePrime(Side face) const
{
    switch (face)
    {
    case Front:
        return rotateX(face)->rotateX(face)->rotateX(face);
    case Back:
        return rotateX(face);

    case Right:
        return rotateY(face)->rotateY(face)->rotateY(face);
    case Left:
        return rotateY(face);

    case Top:
        return rotateZ(face)->rotateZ(face)->rotateZ(face);

    case Bottom:
        return rotateZ(face);

        break;
    default:
        assert(false);
    }
    std::cout << "Bad things are happening" << std::endl;
    return std::make_shared<Rubiks_Cube>(solved_state);
}

bool Rubiks_Cube::is_goal(sp_rubiks_cube_t n) {
    for (int side = 0; side < Num_Sides; side++) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if ( n->current_state[side][row][col] != solved_state[side][row][col]) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::vector<sp_rubiks_cube_t> Rubiks_Cube::successors() {
    std::vector<sp_rubiks_cube_t> list;

    for (int side = 0; side < Num_Sides; side++) {
        list.push_back(this->rotate_side(Side(side)));
        list.push_back(this->rotate_sidePrime(Side(side)));
    }

    return list;
}

int search(std::shared_ptr<std::deque<sp_rubiks_cube_t>> path, int g, int bound, std::unordered_map<std::shared_ptr<Sub_Problem>,int, Sub_Problem_Hasher, Sub_Problem_EqualFn> &h) {
   // std::cout << path->size() << std::endl;
    sp_rubiks_cube_t node = path->back();
    int f = g + h[std::make_shared<Sub_Problem>(*node)];
    if (f > bound) return f;
    if (Rubiks_Cube::is_goal(node)) {
        return FOUND;
    }
    int min = INT_MAX;
    for (sp_rubiks_cube_t succ : node->successors()) {
        if (std::find(path->begin(), path->end(), succ) ==  path->end()) {
            path->push_back(succ);
            int t = search(path, g + 1, bound, h);
            if (t == FOUND) return FOUND;
            if (t < min) {
                min = t;
            }
            path->pop_back();
        }
    }
    return min;
}

std::string get_color(int s) {
    switch(s) {
        case Front:
            return "White";
        case Top:
            return "Red";
        case Left:
            return "Blue"; 
        case Right:
            return "Green";
        case Back:
            return "Yellow";
        case Bottom:
            return "Orange";
        default:
        return "What????11";
    }

}

std::shared_ptr<std::vector<std::string>> path_to_strings(std::shared_ptr<std::deque<sp_rubiks_cube_t>> path) {
    std::shared_ptr<std::vector<std::string>> list = std::make_shared<std::vector<std::string>>();
    for (int i = 0; i + 1 < path->size(); i++) {
        for (int side = 0; side < Num_Sides; side++) {
            if (*((*path)[i]->rotate_side(Side(side))) == *((*path)[i + 1])) {
                list->push_back(get_color(side) + " clockwise");
            }
            if (*((*path)[i]->rotate_sidePrime(Side(side))) == *((*path)[i + 1])) {
                list->push_back(get_color(side) + " counter-clockwise");
            }
        }
    }
    return list;
}

std::shared_ptr<std::vector<std::string>> ida_star(std::shared_ptr<Rubiks_Cube> root, std::unordered_map<std::shared_ptr<Sub_Problem>,int, Sub_Problem_Hasher, Sub_Problem_EqualFn> &h) {
    std::shared_ptr<std::deque<sp_rubiks_cube_t>> path = std::make_shared<std::deque<sp_rubiks_cube_t>>();
    int bound = h[std::make_shared<Sub_Problem>(*root)];
    path->push_back(root);
    for (;;) {
        int t = search(path, 0, bound, h);
        if (t == FOUND) {
            return path_to_strings(path);
        }
        if (t == INT_MAX) {
            return std::make_shared<std::vector<std::string>>();
        }
        bound = t;
    }
}

std::shared_ptr<std::vector<std::string>> Rubiks_Cube::solve() {
    std::unordered_map<std::shared_ptr<Sub_Problem>,int, Sub_Problem_Hasher, Sub_Problem_EqualFn> heuristic;
    
    std::cout << "Starting to read file" << std::endl;

    std::ifstream heuristic_file;
    heuristic_file.open("heurstics.txt");
    std::string line;
    while (std::getline(heuristic_file, line)) {
    //    std::cout << line <<std::endl;
        std::istringstream iss(line);
        int n;
        Color colors[Num_Sides][2][2];
        for (int side = 0; side < Num_Sides; side++) {
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 2; col++) {
                    iss >> n;
                    colors[side][row][col] = Color(n);
                }
            }
        }
        iss >> n;

        heuristic[std::make_shared<Sub_Problem>(colors)] = n;

    }
    std::cout << "Read Heuristic File" << std::endl;
    heuristic_file.close();
    std::shared_ptr<Rubiks_Cube> root = std::make_shared<Rubiks_Cube> (this->current_state);
    return ida_star(root, heuristic);
}
