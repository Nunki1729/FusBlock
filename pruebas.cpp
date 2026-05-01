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
#include <string>
#include <chrono>
#include <thread>
#include <ncurses.h>

#include "src/game/Piece.hpp"
#include "src/game/Grid.hpp"
#include "src/render/render.hpp"

const std::chrono::milliseconds frame_time(16); // ~60 FPS

int main() {
    terminalRender::inicializate();


    Grid grid;
    Piece piece(1, 2);

    auto lastTime = std::chrono::high_resolution_clock::now();
    float accumulator = 0.0f;

    while (1) {
        // Inicio del cronómetro
        auto start = std::chrono::high_resolution_clock::now();
        
        float deltaTime = std::chrono::duration<float>(start - lastTime).count(); // Calculo cuanto tiempo ha pasado en el último frame
        accumulator += deltaTime;

        lastTime = start;

        // Lo q hace en un frame
        int ch = getch();

        if (accumulator > 2.0) { // Tarda 2 s en caer
            piece.fall(grid);
            accumulator -= 2.0f;
        }

        if (ch == 'd' || ch == KEY_RIGHT) piece.move_right(grid);
        if (ch == 'a' || ch == KEY_LEFT) piece.move_left(grid);
        if (ch == 'w' || ch == KEY_UP) piece.rotate(grid);

        terminalRender::show_state(grid, piece);

        // Fin del cronómetro
        auto end = std::chrono::high_resolution_clock::now();
        auto target_frame_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);


        // ¿Debería esperar a q acabe el frame o vamos tarde?
        if (target_frame_time < frame_time) {
        std::this_thread::sleep_for(frame_time - target_frame_time);
    }
    }
    return 0;
}
