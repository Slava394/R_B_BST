cmake_minimum_required(VERSION 3.27)
project(red_black_tree)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        red_black_tree main.cpp
        src/lab4/Stack.h
        src/lab4/RedBlackTree.h
        src/lab4/PrintFunction.h
        test/RedBlackTreeTest.cpp
        test/RedBlackTreeTest.h
        src/interface/CLI.cpp
        src/interface/CLI.h
)
