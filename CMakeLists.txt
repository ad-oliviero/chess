cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "g++")

include(FetchContent)

FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

project(
    chess
    DESCRIPTION "Chess in sfml"
    LANGUAGES CXX
)

add_executable(chess src/location.cpp src/board.cpp src/piece.cpp src/square.cpp src/chess.cpp)

target_link_libraries(chess PRIVATE sfml-graphics sfml-window sfml-system)

