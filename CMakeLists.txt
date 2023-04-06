cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER "clang++")
if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(COMPILE_FLAGS  "-Wall -Wextra -g")
endif()

project(
    chess
    DESCRIPTION "Chess in sfml"
    LANGUAGES CXX
)

add_executable(chess src/board.cpp src/piece.cpp src/square.cpp src/vector2.cpp src/chess.cpp)

target_link_libraries(chess PRIVATE sfml-graphics sfml-window sfml-system)

