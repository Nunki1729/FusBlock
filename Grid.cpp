#include "Grid.hpp"
#include "Piece.hpp"

bool Grid::can_move_left(const Piece& p) {
    if (p.getX() == 0) return 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (p.getCell(i, j) && state[p.getY() - j][p.getX() + i - 1]) return 0;
        }
    }

    return 1;
}

bool Grid::can_move_right(const Piece& p) {
    if (p.getX() == 22) return 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (p.getCell(i, j) && state[p.getY() - j][p.getX() + i + 1]) return 0;
        }
    }

    return 1;
}
