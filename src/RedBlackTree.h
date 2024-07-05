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

    void rotate(Node<T, K> *rotatedNode, Node<T, K> *childNode, bool left, Stack<Node<T, K>*> *path)
    {
        if (left)
        {
            rotatedNode->right = childNode->left;
            childNode->left = rotatedNode;
        }
        else
        {
            rotatedNode->left = childNode->right;
            childNode->right = rotatedNode;
        }
        if (rotatedNode == root)
        {
            root = childNode;
        }
        else
        {
            Node<T, K> *parentNode = path->pop();
            if (parentNode->left == rotatedNode)
            {
                parentNode->left = childNode;
            }
            else
            {
                parentNode->right = childNode;
            }
        }
    }

    void leftRotate(Node<T, K> *rotatedNode, Stack<Node<T, K>*> *path)
    {
        if (rotatedNode->right == nullLeaf)
        {
            return;
        }
        Node<T, K> *rightChild = rotatedNode->right;
        rotate(rotatedNode, rightChild, true, path);
    }

    void rightRotate(Node<T, K> *rotatedNode, Stack<Node<T, K>*> *path)
    {
        if (rotatedNode->left == nullLeaf)
        {
            return;
        }
        Node<T, K> *leftChild = rotatedNode->left;
        rotate(rotatedNode, leftChild, false, path);
    }

    void fixInsertion(Node<T, K> *currentNode, Stack<Node<T, K>*> *path)
    {
        while (!(path->empty()) && path->top()->color == Color::RED)
        {
            Node<T, K> *fatherNode = path->pop();
            if (path->empty())
            {
                break;
            }
            Node<T, K> *grandfatherNode = path->pop();
            bool fatherIsLeftChild = (grandfatherNode->left == fatherNode);
            Node<T, K> *uncleNode = fatherIsLeftChild ? grandfatherNode->right : grandfatherNode->left;
            if (uncleNode->color == Color::RED) //red uncle case
            {
                fatherNode->color = Color::BLACK;
                uncleNode->color = Color::BLACK;
                grandfatherNode->color = Color::RED;
                currentNode = grandfatherNode; //new current node as a grandfather
                continue;
            }
            if (fatherIsLeftChild) // black uncle case (l-r rotate, r rotate)
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
                rightRotate(grandfatherNode, path);
                grandfatherNode->color = Color::RED;
            }
            else // black uncle case (r-l rotate, l rotate)
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
                leftRotate(grandfatherNode, path);
                grandfatherNode->color = Color::RED;
            }
            break;
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
        while (currentNode != nullLeaf)
        {
            path->push(currentNode);
            if (currentNode->key < key)
            {
                currentNode = currentNode->right;
            }
            else if (currentNode->key > key)
            {
                currentNode = currentNode->left;
            }
            else
            { // duplicate case
                delete newNode;
                delete path;
                return;
            }
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
            if (currentNode->color == Color::BLACK)
            {
                blackDeep++;
            }
            else
            {
                redDeep++;
            }
            std::cout << blackDeep << " " << redDeep << "\n";
            return false;
        }
        return true;
    }

    void deleteElement(const T &key)
    {
        Node<T, K> *deletingNode = root;
        auto *path = new Stack<Node<T, K>*>(); //safe path to the new node
        while (deletingNode->key != key)
        {
            if (deletingNode == nullLeaf)
            {
                delete path;
                return;
            }
            path->push(deletingNode);
            if (deletingNode->key < key)
            {
                deletingNode = deletingNode->right;
            }
            else if (deletingNode-> key > key)
            {
                deletingNode = deletingNode->left;
            }
            else
            {
                break;
            }
        }
        Node<T, K> parentNode = path->top();
        if (deletingNode->left != nullLeaf && deletingNode->right != nullLeaf)
        {
            path->push(deletingNode);
            Node<T, K> nextKeyNode = deletingNode->right;
            while (nextKeyNode->left != nullLeaf)
            {
                path->push(nextKeyNode);
                nextKeyNode = nextKeyNode->left;
            }
        }
    }

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
