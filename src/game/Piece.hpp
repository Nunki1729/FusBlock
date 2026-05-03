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

#ifndef PIECE_HPP
#define PIECE_HPP

class Grid;

class Piece {
    public:
        // Constructor
        Piece(const int t, const int r);

        // Getters (para poder ver datos desde fuera)
        int getX() const;
        int getY() const;
        int getType() const;
        int getRotation() const;
        bool getCell(const int y, const int x, const int rotationOverride = -1) const;

        // Movimientos
        bool rotate(const Grid& g);
        bool move_left(const Grid& g);
        bool move_right(const Grid& g);
        bool fall(const Grid& g);

    private:
        const static bool shapes[7][4][4][4];
        int type;
        int rotation;
        int global_x;
        int global_y;
};

#endif
