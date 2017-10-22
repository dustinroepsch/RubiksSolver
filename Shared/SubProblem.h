#ifndef SUB_PROBLEM_H
#define SUB_PROBLEM_H

#include "RubiksCube.h"
#include <boost/functional/hash.hpp>

class Sub_Problem {
public:
    Sub_Problem(const Rubiks_Cube &in_cube);
    Sub_Problem(const Color (&in_colors)[Num_Sides][2][2]);;
    

    inline bool operator==(const Sub_Problem &other) {
        for (int side = 0; side < Num_Sides; side++) {
            for (int row = 0; row < 2; row++) {
                for (int col = 0; col < 2; col++) {
                    if (this->colors[side][row][col] != other.colors[side][row][col]) {
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

    Color colors[Num_Sides][2][2];
};

/**
 * there is definitely a better way to do this
 * */
class Sub_Problem_Hasher
{
public:
  size_t operator() (std::shared_ptr<Sub_Problem> const& key) const
  {
      return key->hash_code();
  }
};
class Sub_Problem_EqualFn
{
public:
  bool operator() (std::shared_ptr<Sub_Problem> const& t1, std::shared_ptr<Sub_Problem> const& t2) const
  {
    return *t1 == *t2;
  }
};

#endif