cmake_minimum_required(VERSION 3.27)
project(red_black_tree)

set(CMAKE_CXX_STANDARD 23)

add_executable(red_black_tree main.cpp
        interface/IEnumerable.h
        interface/IEnumerator.h
        src/TreeIterator.h
        src/RedBlackTree.h
        src/Stack.h
        test/RedBlackTreeTest.cpp
        test/RedBlackTreeTest.h)
