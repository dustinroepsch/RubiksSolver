#ifndef SUB_PROBLEM_H
#define SUB_PROBLEM_H

#include "RubiksCube.h"
#include <boost/functional/hash.hpp>

class Sub_Problem {
public:
    Sub_Problem(const Color (&large_problem)[Num_Sides][3][3]);

    inline bool operator==(const Sub_Problem &other) {
        for (int side = 0; side < Num_Sides; side++) {
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 2; col++) {
                    if (this->colors[side][row][col] != other[side][row][col]) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    inline size_t hash_code() {
        size_t seed = 0;
        for (int side = 0; side < Num_Sides; side++) {
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 2; col++) {
                    boost::hash_combine(seed, int(colors[side][row][col]));
                }
            }
        }
        return seed;
    }
private:
    Color colors[Num_Sides][2][2];
}

#endif