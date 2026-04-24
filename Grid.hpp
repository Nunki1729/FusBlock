#ifndef GRID_HPP
#define GRID_HPP

class Piece;

class Grid {
public:
    Grid();

    // info sobre las piezas en el grid
    bool can_move_left(const Piece& p) const;
    bool can_move_right(const Piece& p) const;
    bool can_fall(const Piece& p) const;

    // Geters
    bool getCell(int y, int x) const;

private:
    bool state[26][16];
};

#endif