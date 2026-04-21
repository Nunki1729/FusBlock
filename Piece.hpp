#ifndef PIECE_HPP
#define PIECE_HPP

class Piece {
public:
    // Constructor
    Piece(const int t, const int r);
    
    // Rotación
    void rotate();

    // Getters (para poder ver datos desde fuera)
    int getX() const;
    int getY() const;

    // Movimientos
    void move_right();
    void move_left();

    // Mostrar figura
    void show();
private:
    static bool shapes[7][4][4][4];
    int type;
    int rotation;
    int x;
    int y;
};

#endif