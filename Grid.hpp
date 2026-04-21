#ifndef GRID_HPP
#define GRID_HPP

#include "Piece.hpp"

class Grid {
public:

    bool can_move_left(const Piece& p);
    bool can_move_right(const Piece& p);

private:
    bool state[24][16];
};

#endif