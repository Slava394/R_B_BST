#pragma once
#include "RedBlackTree.h"


template <typename T>
bool RedBlackTree<T>::TreeIterator::operator==(const TreeIterator &other) const
{
    return current == other.current;
}

template <typename T>
bool RedBlackTree<T>::TreeIterator::operator!=(const TreeIterator &other) const
{
    return !(current == other.current);
}
