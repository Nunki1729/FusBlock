// FusBlock - A terminal-based Tetris implementation in C++
// Copyright (C) 2026  Javier Santiago (Nunki1729)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

bool Grid::can_rotate(const Piece& p) const {
    int virtual_rotation = (p.getRotation() + 1) % 4;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (p.getCell(y, x, virtual_rotation) && state[p.getY() + y][p.getX() + x]) return 0;
        }
    }

    return 1;
}

bool Grid::collides(const Piece& p, const int dy, const int dx, const int rot) const {
    int baseY = p.getY();
    int baseX = p.getX();

    if (baseY + dy < 0 || baseY + dy > 23 || baseX + dx < 0 || baseX + dx > 12) return 1;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (p.getCell(y, x, rot) && state[baseY + dy + y][baseX + dx +x]) return 1;
        }
    }

    return 0;
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

void Grid::pop_raw(const int raw) { // Hacer que las piezas fijas por encima de la fila caigan
//    for (int x = 3; x < 13; x++) {
//        state[raw][x] = 0;
//    }

    for (int y = raw; y > 0; y--) {
        for (int x = 3; x < 13; x++) {
            state[y][x] = state[y - 1][x];
        }
    }
}
