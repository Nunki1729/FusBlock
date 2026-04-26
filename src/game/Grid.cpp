#include "Grid.hpp"
#include "Piece.hpp"

Grid::Grid() : state {
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    } {}

bool Grid::can_move_left(const Piece& p) const {
    if (p.getX() == 0) return 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (p.getCell(y, x) && state[p.getY() + y][p.getX() + x - 1]) return 0;
        }
    }

    return 1;
}

bool Grid::can_move_right(const Piece& p) const {
    if (p.getX() == 12) return 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (p.getCell(y, x) && state[p.getY() + y][p.getX() + x + 1]) return 0;
        }
    }

    return 1;
}

bool Grid::can_fall(const Piece& p) const {
    if (p.getY() == 22) return 0;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (p.getCell(y, x) && state[p.getY() + y + 1][p.getX() + x]) return 0;
        }
    }

    return 1;
}

bool Grid::can_rotate(Piece& p) const {
    int virtual_rotation = (p.getRotation() + 1) % 4;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (p.getCell(y, x, virtual_rotation) && state[p.getY() + y][p.getX() + x]) return 0;
        }
    }

    return 1;
}

bool Grid::getCell(int y, int x) const {
    return state[y][x];
}

void Grid::merge(const Piece& p) {
    int baseY = p.getY();
    int baseX = p.getX();

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            bool& cell = state[baseY + y][baseX + x];
            if (!cell && p.getCell(y, x)) cell = 1;
        }
    }
}
