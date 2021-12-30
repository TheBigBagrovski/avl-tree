cmake_minimum_required(VERSION 3.20)
project(avl-tree C)

set(CMAKE_C_STANDARD 99)

add_library(lib-avl-tree STATIC avl-tree.c)

add_executable(AVL_tree main.c)
add_executable(testExec test.c)

target_link_libraries(AVL_tree lib-avl-tree)
target_link_libraries(testExec lib-avl-tree)