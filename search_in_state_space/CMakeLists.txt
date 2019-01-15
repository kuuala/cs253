cmake_minimum_required(VERSION 3.12)
project(search_in_state_space)

set(CMAKE_CXX_STANDARD 17)

add_executable(search_in_state_space main.cpp Position.hpp Solver.cpp Solver.hpp)