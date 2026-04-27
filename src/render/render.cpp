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

#include <ncurses.h>
#include "render.hpp"
#include "../game/Piece.hpp"
#include "../game/Grid.hpp"

namespace terminalRender
{
    void inicializate() {
    initscr(); // iniciar ncurses
    cbreak(); // input inmediato
    noecho(); // no mostrar teclas
    keypad(stdscr, TRUE); // habilitar flechas
    nodelay(stdscr, TRUE);// no bloquear input
}

void show_state(const Grid& g, const Piece& p) {
    clear();
    int baseX = p.getX();
    int baseY = p.getY();

    auto is_in_piece = [baseX, baseY](int y, int x) {
        return (x >= baseX && x <= baseX + 3) && (y >= baseY && y <= baseY + 3); 
    };
    
    for (int y = 0; y < 26; y++) {
        for (int x = 0; x < 16; x++) {
            int value;
            if (is_in_piece(y, x)) {
                value = (p.getCell(y - baseY, x - baseX) || g.getCell(y, x));
            } else {
                value = g.getCell(y, x);
            }
            mvprintw(y, x * 2, "%d", value);
        }
    }
    refresh();
}
} // namespace terminalRender

