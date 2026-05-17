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
#include "../config/Config.hpp"

std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution<int> distType(0, config::piece::PIECES_NUMBER - 1);
std::uniform_int_distribution<int> distRotation(0, config::piece::ROTATIONS - 1);


// Constructor
Game::Game() : 
    piece(distType(gen), distRotation(gen)), 
    grid(), 
    accumulator(0.0f),
    window(sf::VideoMode(config::window::WIDTH, config::window::HEIGHT), "FusBlock"),
    stats{0, 0, config::game::FALL_DELAY_INITIAL} {

    render::init(window);
}

FallResult Game::fall() {
    FallResult result;

    if (!piece.fall(grid)) {

        grid.merge(piece);

        for (int y = config::grid::PLAY_MIN_Y; y < config::grid::PLAY_MAX_Y; y++) {
            bool full = true;

            for (int x = config::grid::PLAY_MIN_X; x < config::grid::PLAY_MAX_X; x++) { // solo zona jugable
                if (!grid.getCell(y, x)) {
                    full = false;
                    break;
                }
            }

            if (full) {
                grid.popRaw(y);
                result.cleared_rows++;
            }
        }

        piece = Piece(distType(gen), distRotation(gen));
    }

    return result;
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

void Game::updateStats() {
    stats.score = (result.cleared_rows == 4) ? 500 : result.cleared_rows * 100;
    stats.cleared_lines += result.cleared_rows;
    stats.game_over |= result.game_over;
    stats.fall_delay = config::game::FALL_DELAY_MIN + (config::game::FALL_DELAY_INITIAL - config::game::FALL_DELAY_MIN) *
        std::exp(- config::game::DIFFICULTY * stats.cleared_lines);


}

void Game::frame(const float deltaTime) { // Lo que ocurre en un frame
    accumulator += deltaTime;

    render::begin_frame(window);

    // COMIENZO DEL FRAME

    while (accumulator > stats.fall_delay) { // Comprobar si la pieza cae
        result = fall(); // La pieza cae y además la función fall() devuelve el número de filas se han eliminado
        accumulator -= stats.fall_delay;
    }

    updateStats();

    handleInput();

    render::show_state(window, grid, piece);

    render::end_frame(window);

}

bool Game::isRunning() {
    return window.isOpen();
}
