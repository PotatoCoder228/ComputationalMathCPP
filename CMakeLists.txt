cmake_minimum_required(VERSION 3.16)
project(ComputationalMathCPP)
set(CMAKE_CXX_STANDARD 17)
add_executable(ComputationalMathCPP main.cpp Console.cpp Console.h UserCommand.cpp UserCommand.h Equation.cpp Equation.h)