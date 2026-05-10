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

#include <random>
#include <vector>

#include "Piece.hpp"
#include "Grid.hpp"
#include "Game.hpp"

#include "../render/Render.hpp"
#include "../input/Input.hpp"

std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<int> distType(0, 6);
std::uniform_int_distribution<int> distRotation(0, 3);


// Constructor
Game::Game() : 
    piece(distType(gen), distRotation(gen)), 
    grid(), 
    accumulator(0.0f),
    window(sf::VideoMode(800, 800), "FusBlock") {

    render::init(window);
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

        if (full) grid.popRaw(y);
        }

        piece = Piece(distType(gen), distRotation(gen));
    }
}

void Game::handleInput() {
    std::vector<Action> actions = input::poll(window);
    
    for (std::vector<Action>::iterator it = actions.begin(); it != actions.end(); it++) {
        switch (*it) {
            case Action::MoveLeft: 
                piece.moveLeft(grid);
                break;
            case Action::MoveRight: 
                piece.moveRight(grid);
                break;
            case Action::Rotate: 
                piece.rotate(grid);
                break;
            case Action::SoftDrop: 
                piece.fall(grid);
                break;
            case Action::Quit: 
                window.close();
                break;
            default:
                break;
        }
    }
}

void Game::frame(const float deltaTime) { // Lo que ocurre en un frame
    accumulator += deltaTime;

    render::begin_frame(window);

    while (accumulator > 1.0f) { // Tarda 2 s en caer
        fall();
        accumulator -= 1.0f;
    }

    handleInput();

    render::show_state(window, grid, piece);

    render::end_frame(window);

}

bool Game::isRunning() {
    return window.isOpen();
}
