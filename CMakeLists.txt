cmake_minimum_required(VERSION 3.27)
project(red_black_tree)

set(CMAKE_CXX_STANDARD 23)

find_path(READLINE_INCLUDE_DIR readline/readline.h)
find_library(READLINE_LIBRARY NAMES readline)

include_directories(${READLINE_INCLUDE_DIR})

if(NOT READLINE_INCLUDE_DIR OR NOT READLINE_LIBRARY)
    message(FATAL_ERROR "Readline library not found")
endif()

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

target_link_libraries(red_black_tree ${READLINE_LIBRARY})
