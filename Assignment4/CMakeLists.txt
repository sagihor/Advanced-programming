cmake_minimum_required(VERSION 3.29)
project(Assignment4)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment4 main.cpp
        Entity.h
        Entity.cpp
        Room.h
        Room.cpp
        Game.cpp
        Game.h
        Game.cpp)
