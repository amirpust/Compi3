cmake_minimum_required(VERSION 3.14)
project(hw3)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw3 hw3_output.cpp hw3_output.hpp parser.ypp scanner.lex Table.h Exp_t.h Symbol.h Enums.h Exp_t.cpp ObjectsPool.hpp)