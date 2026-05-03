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

#include <iostream>
#include <ncurses.h>
#include <random>

#include "Piece.hpp"
#include "Grid.hpp"
#include "../render/render.hpp"
#include "Game.hpp"

std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<int> distType(0, 6);
std::uniform_int_distribution<int> distRotation(0, 3);


// Constructor
Game::Game() : piece(distType(gen), distRotation(gen)), grid(), accumulator(0.0f) {}

void Game::start() {
    terminalRender::inicializate();
}

void Game::fall() {
    if (!piece.fall(grid)) {

        grid.merge(piece);

        for (int y = grid.PLAY_MIN_Y; y < grid.PLAY_MAX_Y; y++) {
            bool full = true;

            for (int x = grid.PLAY_MIN_X; x < grid.PLAY_MAX_X; x++) { // solo zona jugable
                if (!grid.getCell(y, x)) {
                    full = false;
                    break;
                }
            }

        if (full) grid.pop_raw(y);
        }

        piece = Piece(distType(gen), distRotation(gen));
    }
}

void Game::frame(const float deltaTime) { // Lo que ocurre en un frame
    accumulator += deltaTime;

    while (accumulator > 1.0f) { // Tarda 2 s en caer
        fall();
        accumulator -= 1.0f;
    }

    int ch = getch();

    if (ch == 'd' || ch == KEY_RIGHT) piece.move_right(grid);
    if (ch == 'a' || ch == KEY_LEFT) piece.move_left(grid);
    if (ch == 'w' || ch == KEY_UP) piece.rotate(grid);
    if (ch == 's' || ch == KEY_DOWN) fall();

    terminalRender::show_state(grid, piece);

}
