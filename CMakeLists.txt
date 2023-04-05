cmake_minimum_required(VERSION 3.14)

project(
    chess
    DESCRIPTION "Chess in sfml"
    LANGUAGES CXX
)

add_executable(chess src/location.cpp src/board.cpp src/piece.cpp src/square.cpp src/chess.cpp)

target_link_libraries(chess PRIVATE sfml-graphics sfml-window sfml-system)

