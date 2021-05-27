cmake_minimum_required(VERSION 3.19)
project(rubikscube C)

set(CMAKE_C_STANDARD 99)
set(SOURCES main.c src/enum_types/enum_types.c src/rubiks/rubiks.c)
set(INCLUDES src/enum_types/enum_types.h src/rubiks/rubiks.h)

add_executable(rubikscube ${INCLUDES} ${SOURCES})
