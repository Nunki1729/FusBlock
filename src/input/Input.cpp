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

#include <vector>
#include <SFML/Graphics.hpp>

#include "Input.hpp"
#include "../config/Config.hpp"
#include "../types/Action.hpp"

namespace input {

std::vector<Action> poll(sf::RenderWindow& window) {
    std::vector<Action> actions;
    sf::Event event;

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            actions.push_back(Action::Quit);

        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::A: actions.push_back(Action::MoveLeft); break;
                case sf::Keyboard::D: actions.push_back(Action::MoveRight); break;
                case sf::Keyboard::W: actions.push_back(Action::Rotate); break;
                case sf::Keyboard::S: actions.push_back(Action::SoftDrop); break;

                case sf::Keyboard::Left: actions.push_back(Action::MoveLeft); break;
                case sf::Keyboard::Right: actions.push_back(Action::MoveRight); break;
                case sf::Keyboard::Up: actions.push_back(Action::Rotate); break;
                case sf::Keyboard::Down: actions.push_back(Action::SoftDrop); break;

                default: break;
            }
        }
    }

    actions.push_back(Action::None);

    return actions;
}

}