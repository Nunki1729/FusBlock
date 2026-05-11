cmake_minimum_required(VERSION 3.16)

project(FusBlock)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(FusBlock
    src/main.cpp
    src/game/Game.cpp
    src/game/Grid.cpp
    src/game/Piece.cpp
    src/render/Render.cpp
    src/input/Input.cpp
)

target_link_libraries(FusBlock
    sfml-graphics
    sfml-window
    sfml-system
)