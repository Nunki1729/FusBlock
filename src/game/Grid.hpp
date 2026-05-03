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

#ifndef GRID_HPP
#define GRID_HPP

class Piece;

class Grid {
    public:
        Grid();

        // Constantes
        static constexpr int HEIGHT = 26;
        static constexpr int WEIGHT = 16;

        static constexpr int PLAY_MIN_X = 3;
        static constexpr int PLAY_MAX_X = 13;

        static constexpr int PLAY_MIN_Y = 0;
        static constexpr int PLAY_MAX_Y = 23;

        // info sobre las piezas en el grid
        bool can_move_left(const Piece& p) const;
        bool can_move_right(const Piece& p) const;
        bool can_fall(const Piece& p) const;
        bool can_rotate(const Piece& p) const;

        // Geters
        bool getCell(const int y, const int x) const;

        // Interaction with pieces
        void merge(const Piece& p);
        void pop_raw(const int raw);
        bool collides(const Piece& p, const int dy, const int dx, const int rot) const;

    private:
        bool state[HEIGHT][WEIGHT];
};

#endif
