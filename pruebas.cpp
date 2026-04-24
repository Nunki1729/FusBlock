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
