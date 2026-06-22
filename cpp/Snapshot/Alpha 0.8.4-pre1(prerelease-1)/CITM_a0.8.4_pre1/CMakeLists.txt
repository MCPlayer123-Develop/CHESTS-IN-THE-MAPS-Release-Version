cmake_minimum_required(VERSION 3.20)
project(CITM_a0.8.4_pre1)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXE_LINKER_FLAGS "-mconsole")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack=16777216")

add_executable(CITM_a0.8.4_pre1
        ./Code/main.cpp
        ./Code/game.cpp
        ./Code/entity.cpp
        ./Code/ui.cpp
        ./Code/map.cpp
        Code/save.cpp
        Lib/save.h
)