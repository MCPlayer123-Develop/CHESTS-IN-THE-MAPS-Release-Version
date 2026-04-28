cmake_minimum_required(VERSION 3.20)
project(Project1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-mconsole")

add_executable(Project1
        main.cpp
        game.cpp
        entity.cpp
        ui.cpp
        map.cpp
)