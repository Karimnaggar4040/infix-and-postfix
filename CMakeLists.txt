cmake_minimum_required(VERSION 3.27)
project(infix_and_postfix C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(infix_and_postfix
        project.c)
