#pragma once
#include <iostream>
#include "RedBlackTree.h"
#include "../lab2/ArraySequence.h"


template <typename T>
void RedBlackTree<T>::beautifulPrintTree()
{
    MutableArraySequence<MutableArraySequence<TreeNode*>*> levels;
    fillLevels(levels);
    int maxLevel = levels.GetLength();
    int maxNumberWidth{0};
    for (int index1{0}; index1 < maxLevel; ++index1) {
        for (int index2 = 0; index2 < levels[index1]->GetLength(); ++index2)
        {
            TreeNode *node = levels[index1]->Get(index2);
            int width = node == nullLeaf ? 3 : getNumberWidth(node->key);
            if (width > maxNumberWidth)
            {
                maxNumberWidth = width;
            }
        }
    }
    for (int index1{0}; index1 < maxLevel; ++index1) {
        int spacing = static_cast<int>((pow(2, maxLevel - 1 - index1) - 1) * (maxNumberWidth + 1) + 1);
        std::string prefix = std::string(spacing / 2, ' ');
        std::string separator = std::string(spacing, ' ');
        for (int index2{0}; index2 < levels[index1]->GetLength(); ++index2)
        {
            TreeNode *node = levels[index1]->Get(index2);
            std::string output = node == nullLeaf ? "" : std::to_string(node->key);
            const int padding = maxNumberWidth - static_cast<int>(output.length());
            std::string paddedOutput = std::string(padding / 2 + padding % 2, ' ') + output +
                std::string(padding / 2, ' ');
            std::cout << prefix << paddedOutput;
            if (index2 < levels[index1]->GetLength() - 1)
            {
                prefix = std::string(spacing, ' ');
            }
        }
        std::cout << std::endl;
    }
}


template <typename T>
void RedBlackTree<T>::printHelper(TreeNode *node, std::string indent, bool last) const
{
    if (node != nullLeaf)
    {
        std::cout << indent;
        if (last)
        {
            std::cout << "R----";
            indent += "   ";
        }
        else
        {
            std::cout << "L----";
            indent += "|  ";
        }
        std::string sColor = node->color == Color::RED ? "RED" : "BLACK";
        std::cout << "{" << node->key << "}(" << sColor << ")" << std::endl;
        printHelper(node->left, indent, false);
        printHelper(node->right, indent, true);
    }
}
