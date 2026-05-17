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

namespace config {

    namespace grid {

        constexpr int HEIGHT = 26;
        constexpr int WIDTH = 16;

        constexpr int PLAY_MIN_X = 3;
        constexpr int PLAY_MAX_X = 13;

        constexpr int PLAY_MIN_Y = 0;
        constexpr int PLAY_MAX_Y = 23;

        constexpr int BORDER = 3;

    } 

    namespace piece {

        constexpr int PIECES_NUMBER = 7;
        constexpr int ROTATIONS = 4;
        constexpr int HEIGHT = 4;
        constexpr int WIDTH = 4;

    }

    namespace game {
        constexpr float FALL_DELAY_MIN = 0.1f;
        constexpr float FALL_DELAY_INITIAL = 2.0f;
        constexpr float DIFFICULTY = 0.3f;
    }

    namespace window {
        constexpr int WIDTH = 800;
        constexpr int HEIGHT = 800;
        constexpr int FPS = 60; // 0.0166666667 s per frame
    }

    namespace render {

        constexpr int CELL_SIZE = 30;
        constexpr int OFFSET_X = 50;
        constexpr int OFFSET_Y = 50;

    }

}
