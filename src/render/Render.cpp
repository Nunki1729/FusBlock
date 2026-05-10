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

namespace render
{

    constexpr int CELL_SIZE = 30;
    constexpr int OFFSET_X = 50;
    constexpr int OFFSET_Y = 50;
    

    void init(sf::RenderWindow& window) {
        window.create(sf::VideoMode(800, 800), "FusBlock");
        window.setFramerateLimit(60);
    }

    bool is_open(sf::RenderWindow& window) {
        return window.isOpen();
    }

    void begin_frame(sf::RenderWindow& window) {
        window.clear(sf::Color::Black);
    }

    void show_state(sf::RenderWindow& window, const Grid& g, const Piece& p) {
        int baseX = p.getX();
        int baseY = p.getY();

        auto is_in_piece = [baseX, baseY](int y, int x) {
            return (x >= baseX && x <= baseX + 3) && (y >= baseY && y <= baseY + 3); 
        };

        sf::RectangleShape block(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

        for (int y = g.PLAY_MIN_Y; y < g.PLAY_MAX_Y; y++) {
            for (int x = g.PLAY_MIN_X; x < g.PLAY_MAX_X; x++) {

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
                    OFFSET_X + x * CELL_SIZE,
                    OFFSET_Y + y * CELL_SIZE
                );

                window.draw(block);
            }
        }
    }

    void end_frame(sf::RenderWindow& window) {
        window.display();
    }
}