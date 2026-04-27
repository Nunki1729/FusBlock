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

#include "Piece.hpp"
#include "Grid.hpp"

#include <iostream>

void show_piece(Piece& p) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << p.getCell(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void show_state(Grid& g, Piece& p) {
    int baseX = p.getX();
    int baseY = p.getY();

    auto is_in_piece = [baseX, baseY](int y, int x) {
    return (x >= baseX && x <= baseX + 3) && (y >= baseY && y <= baseY + 3);
    };

    for (int y = 0; y < 26; y++) {
        for (int x = 0; x < 16; x++) {
            if (is_in_piece(y, x)) {
                std::cout << (p.getCell(y - baseY, x - baseX) || g.getCell(y, x)) << ' ';
            }
            else {
                std::cout << g.getCell(y, x) << ' ';
            }
        }
        std::cout << '\n';
    }
}

int main() {
    Piece piece(2, 1);
    Grid grid;

    while (grid.can_move_right(piece)) {
        piece.move_right(grid);
    }


    show_state(grid, piece);

    return 0;
}
