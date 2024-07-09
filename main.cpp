#include <iostream>
#include <random>
#include <chrono>
#include "src/RedBlackTree.h"
#define NUMBER 12


int longComparator(const long &a, const long &b)
{
    if (a < b)
        return 1;
    if (a == b)
        return 0;
    return -1;
}

void newLongComparator(const long &a, const long &b);


int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrab(1, 999);
    auto *rbt1 = new RedBlackTree<long>(longComparator);
    for (int index{0}; index < 10; ++index)
    {
        rbt1->insertElement(distrab(gen));
    }
    rbt1->beautifulPrintTree();
    rbt1->printTree();
    rbt1->map([](long &a){ a *= 2;});
    rbt1->insertElement(999);
    const auto *a = rbt1->searchElement(999);
    std::cout << a->key << std::endl;
    rbt1->printTree();
    auto *rbt2 = rbt1->where([](long &a) { return a < 1000 && a > 600;} );
    rbt2->beautifulPrintTree();
    rbt2->printTree();
    std::cout << rbt2->reduce(0, [](const long &a, const long &b){return a + b;}) << std::endl;
    delete rbt1;
    delete rbt2;
    return 0;
}
