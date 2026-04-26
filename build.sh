#!/bin/bash

# Crear carpeta build si no existe
mkdir -p build

# Compilar
g++ scr/main.cpp scr/game/*.cpp scr/render/*.cpp -o build/main -lncurses

echo "✔ Compilado en build/main"