cmake_minimum_required(VERSION 3.22)
project(biominal_heap C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS "-O0 -Wall -g -v -fsanitize=address -fno-omit-frame-pointer ")
add_executable(biominal_heap main.c)
target_compile_options(biominal_heap PRIVATE -O0 -Wall -g -v -fsanitize=address -fno-omit-frame-pointer)