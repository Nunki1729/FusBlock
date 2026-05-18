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

#pragma once

#include <SFML/Graphics.hpp>
#include "../config/Config.hpp"

#include "../types/RenderData.hpp"

class Grid;
class Piece;

struct GameStats;

class Render {
    public:
    Render(sf::RenderWindow& w, const Piece& p, const Grid& g, const GameStats& s);

    void beginFrame();
    void endFrame();
    void updateWindow();

    void updateData(const RenderData& d);

    private:
    void showState();

    sf::RenderWindow& window;
    sf::Font font;

    const RenderData data;
};
