#pragma once
#include <iostream>
#include <cmath>
#include "RedBlackTree.h"
#include "../lab2/ArraySequence.h"


//get number length
template <typename T>
int getNumberWidth(T number)
{   //get number width
    int width = 0;
    if (number < 0) ++width;
    while (number != 0)
    {
        number /= 10;
        width++;
    }
    return width;
}
//beautiful output
void beautifulPrintTree(RedBlackTree<long> *rbt)
{
    MutableArraySequence<MutableArraySequence<RedBlackTree<long>::TreeNode*>*> levels;
    fillLevels(levels, rbt);
    int maxLevel = levels.GetLength();
    int maxNumberWidth{0};
    for (int index1{0}; index1 < maxLevel; ++index1) {
        for (int index2 = 0; index2 < levels[index1]->GetLength(); ++index2)
        {
            RedBlackTree<long>::TreeNode *node = levels[index1]->Get(index2);
            int width = node == rbt->nullLeaf ? 3 : getNumberWidth(node->key);
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
            RedBlackTree<long>::TreeNode *node = levels[index1]->Get(index2);
            std::string output = node == rbt->nullLeaf ? "" : std::to_string(node->key);
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
//help function for pretty number output
void fillLevels(MutableArraySequence<MutableArraySequence<RedBlackTree<long>::TreeNode*>*> &levels,
                RedBlackTree<long> *rbt)
{
    levels.Append(new MutableArraySequence<RedBlackTree<long>::TreeNode*>());
    levels[0]->Append(rbt->root);
    int currentLevel = 0;
    while (currentLevel < levels.GetLength()) {
        MutableArraySequence<RedBlackTree<long>::TreeNode*> *current = levels[currentLevel];
        auto *nextLevel = new MutableArraySequence<RedBlackTree<long>::TreeNode*>();
        bool hasValidNode = false;
        for (int index{0}; index < current->GetLength(); ++index)
        {
            RedBlackTree<long>::TreeNode *node = current->Get(index);
            if (node != rbt->nullLeaf)
            {
                hasValidNode = true;
                nextLevel->Append(node->left);
                nextLevel->Append(node->right);
            }
            else
            {
                nextLevel->Append(rbt->nullLeaf);
                nextLevel->Append(rbt->nullLeaf);
            }
        }
        if (!hasValidNode)
        {
            delete nextLevel;
            break;
        }
        levels.Append(nextLevel);
        ++currentLevel;
    }
}
