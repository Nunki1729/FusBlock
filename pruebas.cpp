#include "Piece.hpp"
#include "Grid.hpp"

int main() {
    Piece a(1, 2);
    a.show();
    a.rotate();
    a.show();

    Grid g;
    return 0;
}