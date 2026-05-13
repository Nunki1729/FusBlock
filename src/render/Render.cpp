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

#include <SFML/Graphics.hpp>
#include "Render.hpp"
#include "../game/Piece.hpp"
#include "../game/Grid.hpp"
#include "../config/Config.hpp"

namespace render
{
    
void init(sf::RenderWindow& window) {
    window.setFramerateLimit(config::window::FPS);
}

void begin_frame(sf::RenderWindow& window) {
        window.clear(sf::Color::Black);
    }

void show_state(sf::RenderWindow& window, const Grid& g, const Piece& p) {
        int baseX = p.getX();
        int baseY = p.getY();

        auto is_in_piece = [baseX, baseY](int y, int x) {
            return (x >= baseX && x <= baseX + config::piece::WIDTH - 1) && (y >= baseY && y <= baseY + config::piece::HEIGHT - 1); 
        };

        sf::RectangleShape block(sf::Vector2f(config::render::CELL_SIZE - 1, config::render::CELL_SIZE - 1));

        for (int y = config::grid::PLAY_MIN_Y; y < config::grid::PLAY_MAX_Y; y++) {
            for (int x = config::grid::PLAY_MIN_X; x < config::grid::PLAY_MAX_X; x++) {

                int value;

                if (is_in_piece(y, x)) {
                    value = (p.getCell(y - baseY, x - baseX) || g.getCell(y, x));
                } else {
                    value = g.getCell(y, x);
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

void end_frame(sf::RenderWindow& window) {
        window.display();
    }

}
