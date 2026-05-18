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

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "Render.hpp"
#include "../game/Piece.hpp"
#include "../game/Grid.hpp"
#include "../config/Config.hpp"

#include "../types/RenderData.hpp"
#include "../types/GameStats.hpp"
    
Render::Render(sf::RenderWindow& w, const Piece& p, const Grid& g, const GameStats& s):
    window(w),
    data{p, g, s} {
    window.setFramerateLimit(config::window::FPS);
    if (!font.loadFromFile("assets/fonts/dev_font/TrainOne-Regular.ttf")) {
        std::cout << "FONT FAILED\n";
}
}

void Render::beginFrame() {
        window.clear(sf::Color::Black);
    }

void Render::endFrame() {
        window.display();
    }

void Render::showState() {
        int baseX = data.piece.getX();
        int baseY = data.piece.getY();

        auto is_in_piece = [baseX, baseY](int y, int x) {
            return (x >= baseX && x <= baseX + config::piece::WIDTH - 1) && (y >= baseY && y <= baseY + config::piece::HEIGHT - 1); 
        };

        sf::RectangleShape block(sf::Vector2f(config::render::CELL_SIZE - 1, config::render::CELL_SIZE - 1));

        for (int y = config::grid::PLAY_MIN_Y; y < config::grid::PLAY_MAX_Y; y++) {
            for (int x = config::grid::PLAY_MIN_X; x < config::grid::PLAY_MAX_X; x++) {

                bool value;

                if (is_in_piece(y, x)) {
                    value = (data.piece.getCell(y - baseY, x - baseX) || data.grid.getCell(y, x));
                } else {
                    value = data.grid.getCell(y, x);
                }

                if (value) {
                    block.setFillColor(sf::Color::White);
                } else {
                    block.setFillColor(sf::Color(30, 30, 30));
                }

                block.setPosition(
                    config::render::OFFSET_X + x * config::render::CELL_SIZE,
                    config::render::OFFSET_Y + y * config::render::CELL_SIZE
                );

                window.draw(block);
            }
        }
    }

void Render::showText() {

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);

    float hudX = config::grid::PLAY_MAX_X * config::render::CELL_SIZE + 100;

    // SCORE
    text.setString("Score: " + std::to_string(data.stats.score));
    text.setFillColor(sf::Color::Red);
    text.setPosition(hudX, 50.f);
    window.draw(text);

    // LINES
    text.setString("Cleared lines: " + std::to_string(data.stats.cleared_lines));
    text.setFillColor(sf::Color::White);
    text.setPosition(hudX, 90.f);
    window.draw(text);
}

void Render::updateWindow() {
    showState();
    showText();
}
