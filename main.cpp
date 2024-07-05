#include <iostream>
#include <random>
#include <chrono>
#include "src/RedBlackTree.h"
#define NUMBER 40000


int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution distrib(-10000000, 10000000);
    RedBlackTree<long, long> rbt;
    for (long index{0}; index < NUMBER; ++index)
    {
        rbt.insertElement(1 + index, 0);
    }
    // rbt.printTree();
    std::cout << rbt.getBlackHeight() << std::endl;
    const auto start = std::chrono::high_resolution_clock::now();
    for (long index{NUMBER - 1}; index >=
        0 ; --index)
    {
        rbt.deleteElement(1 + index);
        if (rbt.getBlackHeight() == -1) throw;
    }
    const auto end = std::chrono::high_resolution_clock::now();
    // rbt.printTree();
    std::cout << rbt.getBlackHeight() << std::endl;
    const std::chrono::duration<double> elapsed = end - start;
    std::cout << elapsed / NUMBER << std::endl;
    return 0;
}
