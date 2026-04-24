#ifndef PIECE_HPP
#define PIECE_HPP

class Grid;

class Piece {
public:
    // Constructor
    Piece(const int t, const int r);
    
    // Rotación
    void rotate();

    // Getters (para poder ver datos desde fuera)
    int getX() const;
    int getY() const;
    int getType() const;
    int getRotation() const;
    bool getCell(int y, int x) const;

    // Movimientos
    void move_left(const Grid& g);
    void move_right(const Grid& g);
    void fall(const Grid& g);

private:
    static bool shapes[7][4][4][4];
    int type;
    int rotation;
    int global_x;
    int global_y;
};

#endif