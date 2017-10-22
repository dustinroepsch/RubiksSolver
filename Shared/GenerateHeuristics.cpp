#include "RubiksCube.h"
#include "SubProblem.h"

#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>

int main() {

    sp_rubiks_cube_t cube = std::make_shared<Rubiks_Cube>(Rubiks_Cube::solved_state);

    std::unordered_map<std::shared_ptr<Sub_Problem>,int, Sub_Problem_Hasher, Sub_Problem_EqualFn> map;

    std::queue<sp_rubiks_cube_t> queue;
    queue.push(cube);
    int distance = 0;
    map[std::make_shared<Sub_Problem>(*cube)] = distance;
    int last_distance = 0;
    
    while (!queue.empty()){
        cube = queue.front();
        queue.pop();
        distance = map[std::make_shared<Sub_Problem>(*cube)];
        if (distance != last_distance) {
            std::cout << "distance: " << distance << " queue size: " << queue.size() << " map size: " << map.size() << "\n";
            last_distance = distance;
        }
      

        for (int side = 0; side < Num_Sides; side++) {
          
            
            sp_rubiks_cube_t next_cube = cube->rotate_side(Side(side));
            std::shared_ptr<Sub_Problem> sub = std::make_shared<Sub_Problem>(*next_cube);
            if (map.count(sub) == 0) {
                map[sub] = distance + 1;
                queue.push(next_cube);
            } else {
             //   std::cout << "collided" << std::endl;
            }

            next_cube = cube->rotate_sidePrime(Side(side));
            sub = std::make_shared<Sub_Problem>(*next_cube);
            if (map.count(sub) == 0) {
                map[sub] = distance + 1;
                queue.push(next_cube);
            } else {
            //    std::cout << "collided2" << std::endl;
                
            }
        }


    }

    std::ofstream output_file;
    output_file.open("heurstics.txt");

    for (std::pair<std::shared_ptr<Sub_Problem>,int> pair : map) {
        for (int side = 0; side < Num_Sides; side++) {
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 2; col++) {
                    output_file << pair.first->colors[side][row][col] << " ";
                }
            }
        }
        output_file  << pair.second << std::endl;
    }

    output_file.close();


    return 0;
}