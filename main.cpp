#include <iostream>
#include "src/RedBlackTree.h"
#define NUMBER 1000000


int main()
{
    RedBlackTree<long, long> rbt;
    time_t t0 = time(nullptr);
    for (long index{0}; index < NUMBER; index++)
    {
        rbt.insertElement(rand(), 2 * index);
    }
    time_t t1 = time(nullptr);
    double time_in_seconds = difftime(t1, t0) / NUMBER;
    std::cout << time_in_seconds << "\n";
    std::cout << rbt.searchElement(-8786657) << "\n";
    std::cout << rbt.searchElement(-35345) << "\n";
    std::cout << rbt.searchElement(20) << "\n";
    std::cout << rbt.searchElement(78787) << "\n";
    std::cout << rbt.searchElement(234546) << "\n";
    std::cout << rbt.searchElement(324348) << "\n";
//    for (long index = 1; index <= 20; ++index)
//    {
//        rbt.insertElement(rand() % 100, 2L);
//        rbt.printTree();
//        std::cout << std::endl;
//    }
//
//    rbt.searchElement(93);
//    rbt.searchElement(36);
    return 0;
}
