#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ncurses.h>

const std::chrono::milliseconds frame_time(16); // ~60 FPS

#include "Piece.hpp"
#include "Grid.hpp"

void show_state(Grid& g, Piece& p);

int main() {
    initscr();            // iniciar ncurses
    cbreak();             // input inmediato
    noecho();             // no mostrar teclas
    keypad(stdscr, TRUE); // habilitar flechas
    nodelay(stdscr, TRUE);// no bloquear input


    Grid grid;
    Piece piece(1, 2);



    std::cout << "Piece rotation: ";
    std::cout << "Piece position Y: ";
    std::cout << "Piece position X: ";

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

        clear(); // limpiar pantalla

        if (accumulator > 2.0) { // Tarda 2 s en caer
            piece.fall(grid);
            accumulator -= 2.0f;
        }

        if (ch == 'd' || ch == KEY_RIGHT) piece.move_right(grid);
        if (ch == 'a' || ch == KEY_LEFT) piece.move_left(grid);
        if (ch == 'w' || ch == KEY_UP) piece.rotate();

        show_state(grid, piece);
        refresh();

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

void show_state(Grid& g, Piece& p) {
    int baseX = p.getX();
    int baseY = p.getY();

    auto is_in_piece = [baseX, baseY](int y, int x) {
        return (x >= baseX && x <= baseX + 3) && (y >= baseY && y <= baseY + 3);
    };

    for (int y = 0; y < 26; y++) {
        for (int x = 0; x < 16; x++) {
            int value;

            if (is_in_piece(y, x)) {
                value = (p.getCell(y - baseY, x - baseX) || g.getCell(y, x));
            } else {
                value = g.getCell(y, x);
            }

            mvprintw(y, x * 2, "%d", value);
        }
    }
}
