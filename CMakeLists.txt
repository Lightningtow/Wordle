cmake_minimum_required(VERSION 3.21)
project(wordle)

set(CMAKE_CXX_STANDARD 14)

add_executable(wordle wordlegame.cpp Wordle.cpp Wordle.h)
