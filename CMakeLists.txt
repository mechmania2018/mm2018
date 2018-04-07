cmake_minimum_required(VERSION 3.5)
project(mm2018)

set(CMAKE_CXX_STANDARD 14)

add_executable(game Game.cpp Game.h Monster.cpp Monster.h Player.cpp Player.h Unit.cpp Unit.h types.h main.cpp)
