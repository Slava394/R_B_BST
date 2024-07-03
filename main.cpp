#include <iostream>
#include "src/RedBlackTree.h"


std::ostream& operator<<(std::ostream& out, const Color& color)
{
    switch (color)
    {
        case Color::RED:
            out << "RED";
            break;
        case Color::BLACK:
            out << "BLACK";
            break;
    }
    return out;
}

int main()
{
    RedBlackTree<long, long> rbt;
    for (long index{0}; index < 10000000; index++)
    {
        rbt.insertElement(index + 1, 2 * index);
    }
    for (long index{0}; index < 10000000; index++)
    {
        rbt.searchElement(index + 1);
    }
    return 0;
}
