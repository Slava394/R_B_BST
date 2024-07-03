#pragma once
#include "Stack.h"


enum class Color : bool
{
    RED,
    BLACK
};


template <typename T, typename K>
struct Node
{
public:
    T key;
    K data;
    Color color;
    Node *left, *right;
    explicit Node(const T &key,
                  const K &data,
                  Color color,
                  Node *left = nullptr,
                  Node *right = nullptr)
        : key(key), data(data), color(color), left(left), right(right) {}
};


template <typename T, typename K>
class RedBlackTree
{
private:
    Node<T, K> *root;
    Node<T, K> *nullLeaf;

    void leftRotate(Node<T, K> *rotatedNode, Stack<Node<T, K>*> *path)
    {
        if (rotatedNode->right == nullLeaf)
        {
            return;
        }
        Node<T, K> *rightChild = rotatedNode->right;
        rotatedNode->right = rightChild->left;
        if (rotatedNode == root)
        {
            root = rightChild;
        }
        else
        {
            Node<T, K> *fatherNode = path->pop();
            if (fatherNode->left == rotatedNode)
            {
                fatherNode->left = rightChild;
            }
            else
            {
                fatherNode->right = rightChild;
            }
        }
        rightChild->left = rotatedNode;
    }

    void rightRotate(Node<T, K> *rotatedNode, Stack<Node<T, K>*> *path)
    {
        if (rotatedNode->left == nullLeaf)
        {
            return;
        }
        Node<T, K> *leftChild = rotatedNode->left;
        rotatedNode->left = leftChild->right;
        if (rotatedNode == root)
        {
            root = leftChild;
        }
        else
        {
            Node<T, K> *fatherNode = path->pop();
            if (fatherNode->left == rotatedNode)
            {
                fatherNode->left = leftChild;
            }
            else
            {
                fatherNode->right = leftChild;
            }
        }
        leftChild->right = rotatedNode;
    }

    void fixInsertion(Node<T, K> *currentNode, Stack<Node<T, K>*> *path)
    {
        if (path->empty())
        {
            currentNode->color = Color::BLACK; //R-B BST property
            return;
        }
        while (!(path->empty()) && path->top()->color == Color::RED)
        {
            Node<T, K> *fatherNode = path->pop();
            Node<T, K> *grandfatherNode = path->pop();
            if  (grandfatherNode->left == fatherNode)
            {
                Node<T, K> *uncleNode = grandfatherNode->right;
                if (uncleNode->color == Color::RED)
                {
                    fatherNode->color = Color::BLACK;
                    uncleNode->color = Color::BLACK;
                    grandfatherNode->color = Color::RED;
                    currentNode = grandfatherNode; //repeat for grandfather
                }
                else
                {
                    if (currentNode == fatherNode->right)
                    {
                        path->push(grandfatherNode);
                        leftRotate(fatherNode, path);
                        currentNode->color = Color::BLACK;
                    }
                    else
                    {
                        fatherNode->color = Color::BLACK;
                    }
                    grandfatherNode->color = Color::RED;
                    rightRotate(grandfatherNode, path);
                    break;
                }
            }
            else
            {
                Node<T, K> *uncleNode = grandfatherNode->left;
                if (uncleNode->color == Color::RED)
                {
                    fatherNode->color = Color::BLACK;
                    uncleNode->color = Color::BLACK;
                    grandfatherNode->color = Color::RED;
                    currentNode = grandfatherNode; //repeat for grandfather
                }
                else
                {
                    if (currentNode == fatherNode->left)
                    {
                        path->push(grandfatherNode);
                        rightRotate(fatherNode, path);
                        currentNode->color = Color::BLACK;
                    }
                    else
                    {
                        fatherNode->color = Color::BLACK;
                    }
                    grandfatherNode->color = Color::RED;
                    leftRotate(grandfatherNode, path);
                    break;
                }
            }
        }
        root->color = Color::BLACK;
    }
public:
    RedBlackTree()
    {
        nullLeaf = new Node<T, K>(T(), K(), Color::BLACK);
        root = nullLeaf;
    }

    void insertElement(const T &key, const T &value)
    {
        auto *newNode = new Node<T, K>(key, value, Color::RED, nullLeaf, nullLeaf);
        auto *path = new Stack<Node<T, K>*>(); //safe path to the new node
        Node<T, K> *currentNode = root;
        while (currentNode != nullLeaf && currentNode->key != key)
        {
            path->push(currentNode);
            if (currentNode->key < key)
            {
                currentNode = currentNode->right;
            }
            else
            {
                currentNode = currentNode->left;
            }
        }
        if (currentNode != nullLeaf && currentNode->key == key)
        {
            delete newNode; //node is already exist
            return;
        }
        if (path->empty())
        {
            root = newNode;
        }
        else
        {
            Node<T, K> *fatherNode = path->top();
            if (fatherNode->key < key)
            {
                fatherNode->right = newNode;
            }
            else
            {
                fatherNode->left = newNode;
            }
        }
        fixInsertion(newNode, path);
        delete path;
    }

    bool searchElement(const T &key)
    {
        Node<T, K> *currentNode = root;
        int blackDeep = 0, redDeep = 0;
        while (currentNode != nullLeaf && currentNode->key != key)
        {
            if (currentNode->color == Color::BLACK)
            {
                blackDeep++;
            }
            else
            {
                redDeep++;
            }
            if (currentNode->key < key)
            {
                currentNode = currentNode->right;
            }
            else
            {
                currentNode = currentNode->left;
            }
        }
        if (currentNode == nullLeaf)
        {
            return false;
        }
        if (currentNode->color == Color::BLACK)
        {
            blackDeep++;
        }
        else
        {
            redDeep++;
        }
        std::cout << blackDeep << " " << redDeep << "\n";
        return true;
    }

//    void deleteElement(const T &key)
//    {
//        Node<T, K> *currentNode = root;
//        while (currentNode != nullLeaf && currentNode->key != key)
//        {
//            if (currentNode->key < key)
//            {
//                currentNode = currentNode->right;
//            }
//            else
//            {
//                currentNode = currentNode->left;
//            }
//        }
//        if (currentNode == nullLeaf)
//        {
//            return;
//        }
//        if (currentNode->left == nullLeaf && currentNode->right == nullLeaf)
//        {
//            if (currentNode == root)
//            {
//                root = nullLeaf;
//            }
//            else
//            {
//                if (currentNode->parent->left == currentNode)
//                {
//                    currentNode->parent->left = nullLeaf;
//                }
//                else
//                {
//                    currentNode->parent->right = nullLeaf;
//                }
//            }
//            delete currentNode;
//            return;
//        }
//        else if (currentNode->left == nullLeaf || currentNode->right == nullLeaf)
//        {
//            Node<T, K> *onlyChild;
//            if (currentNode->left == nullLeaf)
//            {
//                onlyChild = currentNode->right;
//            }
//            else
//            {
//                onlyChild = currentNode->left;
//            }
//            if (currentNode == root)
//            {
//                onlyChild->parent = nullLeaf;
//                root = onlyChild;
//            }
//            else
//            {
//                onlyChild->parent = currentNode->parent;
//                if (onlyChild->parent->left == currentNode)
//                {
//                    onlyChild->parent->left = onlyChild;
//                }
//                else
//                {
//                    onlyChild->parent->right = onlyChild;
//                }
//            }
//            delete currentNode;
//        }
//        else
//        {
//            Node<T, K> *rightSubtreeRoot = currentNode->right;
//            if (currentNode == root)
//            {
//                rightSubtreeRoot->parent = nullLeaf;
//
//            }
//            else
//            {
//                rightSubtreeRoot->parent = currentNode->parent;
//                if (rightSubtreeRoot->parent != nullLeaf)
//                {
//                    if (rightSubtreeRoot->parent->left == currentNode)
//                    {
//                        rightSubtreeRoot->parent->left = rightSubtreeRoot;
//                    }
//                    else
//                    {
//                        rightSubtreeRoot->parent->right = rightSubtreeRoot;
//                    }
//                }
//                else
//                {
//                    root = rightSubtreeRoot;
//                }
//                rightSubtreeRoot->left = currentNode->left;
//                if (rightSubtreeRoot->left != nullLeaf)
//                {
//                    rightSubtreeRoot->left->parent =  rightSubtreeRoot;
//                }
//                delete currentNode;
//            }
//            else
//            {
//                Node<T, K> *leftMostNode = rightSubtreeRoot->left;
//                while (leftMostNode->left != nullLeaf)
//                {
//                    leftMostNode = leftMostNode->left;
//                }
//                leftMostNode->parent->left = nullLeaf;
//                leftMostNode->parent = currentNode->parent;
//                if (leftMostNode->parent != nullLeaf)
//                {
//                    if (leftMostNode->parent->left == currentNode)
//                    {
//                        leftMostNode->parent->left = leftMostNode;
//                    }
//                    else
//                    {
//                        leftMostNode->parent->right = leftMostNode;
//                    }
//                }
//                leftMostNode->left = currentNode->left;
//                leftMostNode->right = currentNode->right;
//                currentNode->right->parent = leftMostNode;
//                if (leftMostNode->left != nullLeaf)
//                {
//                    leftMostNode->left->parent = leftMostNode;
//                }
//                delete currentNode;
//            }
//        }
//    }

    void printHelper(Node<T, K> *node, std::string indent, bool last) const
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
            std::cout << node->key << "(" << sColor << ")" << std::endl;
            printHelper(node->left, indent, false);
            printHelper(node->right, indent, true);
        }
    }

    void printTree() const
    {
        if (root)
        {
            printHelper(root, "", true);
        }
    }
};
