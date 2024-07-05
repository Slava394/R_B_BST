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
            Node<T, K> *parentNode = path->top();
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

    void fixInsertion(Node<T, K> *currentNode, Stack<Node<T, K>*> *path) //for balance after insertion
    {
        while (!path->empty() && path->top()->color == Color::RED)
        {
            Node<T, K> *fatherNode = path->pop();
            if (path->empty())
            {
                break;
            }
            Node<T, K> *grandfatherNode = path->pop();
            bool fatherIsLeftChild = grandfatherNode->left == fatherNode;
            if (Node<T, K> *uncleNode = fatherIsLeftChild ?
                grandfatherNode->right : grandfatherNode->left; uncleNode->color == Color::RED) //red uncle case
            {
                fatherNode->color = Color::BLACK;
                uncleNode->color = Color::BLACK;
                grandfatherNode->color = Color::RED;
                currentNode = grandfatherNode; //new current node as a grandfather
                continue;
            }
            if (fatherIsLeftChild) //black uncle case (l-r rotate, r rotate)
            {
                if (currentNode == fatherNode->right)
                {
                    path->push(grandfatherNode);
                    leftRotate(fatherNode, path);
                    path->pop();
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
                    path->pop();
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

    void fixDeletion(Node<T, K> *currentNode, Stack<Node<T, K>*> *path)
    {
        while (!path->empty()) {
            Node<T, K> *fatherNode = path->pop();
            Node<T, K> *brotherNode = fatherNode->left == currentNode ?
                fatherNode->right : fatherNode->left;
            if (brotherNode->color == Color::BLACK)
            {
                if (fatherNode->right == brotherNode)
                {
                    if (brotherNode->right->color == Color::RED)
                    {
                        Color fatherColor = fatherNode->color;
                        fatherNode->color = Color::BLACK;
                        brotherNode->right->color = Color::BLACK;
                        brotherNode->color = fatherColor;
                        leftRotate(fatherNode, path);
                    }
                    else if (brotherNode->left->color == Color::RED && brotherNode->right->color == Color::BLACK)
                    {
                        brotherNode->color = Color::RED;
                        brotherNode->left->color = Color::BLACK;
                        Node<T, K> *newBrotherNode = brotherNode->left;
                        path->push(fatherNode);
                        rightRotate(brotherNode, path);
                        path->pop();
                        Color fatherColor = fatherNode->color;
                        fatherNode->color = newBrotherNode->right->color = Color::BLACK;
                        newBrotherNode->color = fatherColor;
                        leftRotate(fatherNode, path);
                    }
                    else
                    {
                        brotherNode->color = Color::RED;
                        if (fatherNode->color == Color::RED)
                        {
                            fatherNode->color = Color::BLACK;
                        }
                        else
                        {
                            currentNode = fatherNode;
                            continue;
                        }
                    }
                }
                else
                {
                    if (brotherNode->left->color == Color::RED)
                    {
                        Color fatherColor = fatherNode->color;
                        fatherNode->color = Color::BLACK;
                        brotherNode->left->color = Color::BLACK;
                        brotherNode->color = fatherColor;
                        rightRotate(fatherNode, path);
                    }
                    else if (brotherNode->right->color == Color::RED && brotherNode->left->color == Color::BLACK)
                    {
                        brotherNode->color = Color::RED;
                        brotherNode->right->color = Color::BLACK;
                        Node<T, K> *newBrotherNode = brotherNode->right;
                        path->push(fatherNode);
                        leftRotate(brotherNode, path);
                        path->pop();
                        Color fatherColor = fatherNode->color;
                        fatherNode->color = newBrotherNode->left->color = Color::BLACK;
                        newBrotherNode->color = fatherColor;
                        rightRotate(fatherNode, path);
                    }
                    else
                    {
                        brotherNode->color = Color::RED;
                        if (fatherNode->color == Color::RED)
                        {
                            fatherNode->color = Color::BLACK;
                        }
                        else
                        {
                            currentNode = fatherNode;
                            continue;
                        }
                    }
                }
            }
            else
            {
                fatherNode->color = Color::RED;
                brotherNode->color = Color::BLACK;
                if (fatherNode->right == brotherNode)
                {
                    leftRotate(fatherNode, path);
                }
                else
                {
                    rightRotate(fatherNode, path);
                }
                path->push(brotherNode);
                path->push(fatherNode);
                continue;
            }
            break;
        }
    }

    int getBlackHeightOfNode(Node<T, K> *node) //for balance check
    {
        if (node == nullLeaf)
        {
            return 0;
        }
        int leftHeight = getBlackHeightOfNode(node->left);
        int rightHeight = getBlackHeightOfNode(node->right);
        if (leftHeight == -1 || rightHeight == -1 || leftHeight  != rightHeight)
        {
            return -1;
        }
        return leftHeight + (node->color == Color::BLACK ? 1 : 0);
    }

    void deleteNode(Node<T, K> *node)
    {
        if (node->left)
        {
            deleteNode(node->left);
        }
        if (node->right)
        {
            deleteNode(node->right);
        }
        if (node != nullLeaf)
        {
            delete node;
        }
    }
public:
    RedBlackTree()
    {
        nullLeaf = new Node<T, K>(T(), K(), Color::BLACK);
        root = nullLeaf;
    }

    ~RedBlackTree()
    {
        clearTree();
        delete nullLeaf;
    }

    void insertElement(const T &key, const T &value)
    {
        auto *newNode = new Node<T, K>(key, value, Color::RED, nullLeaf, nullLeaf);
        auto *path = new Stack<Node<T, K>*>(); //save path to the new node
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
        auto *path = new Stack<Node<T, K>*>(); //save path to the deleting node
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
        //if the node was not found
        if (currentNode == nullLeaf)
        {
            delete path;
            return;
        }
        if (currentNode->left == nullLeaf || currentNode->right == nullLeaf)
        {
            Node<T, K> *childNode = currentNode->left == nullLeaf ?
                currentNode->right : currentNode->left;
            if (currentNode == root)
            {
                root = childNode;
            }
            else
            {
                Node<T, K> *fatherNode = path->top();
                if (currentNode->left == nullLeaf && currentNode->right == nullLeaf && currentNode->color == Color::BLACK)
                {
                    fixDeletion(currentNode, path);
                }
                if (fatherNode->left == currentNode)
                {
                    fatherNode->left = childNode;
                }
                else
                {
                    fatherNode->right = childNode;
                }
            }
            if (childNode != nullLeaf)
            {
                childNode->color = Color::BLACK;
            }
        }
        else //node with two child
        {
            Node<T, K> *nextKeyNode = currentNode->right;
            Node<T, K> *fatherOfDeletingNode;
            if (currentNode != root)
            {
                fatherOfDeletingNode = path->top();
            }
            path->push(currentNode);
            int count = 1;
            while (nextKeyNode->left != nullLeaf)
            {
                path->push(nextKeyNode);
                nextKeyNode = nextKeyNode->left;
                count++;
            }
            Node<T, K> *fatherOfSwapingNode = path->top();
            Color deletingNodeColor = currentNode->color;
            Color swapingNodeColor = nextKeyNode->color;
            Node<T, K> *tempNode = currentNode->right;
            currentNode->right = nextKeyNode->right;
            if (currentNode == root)
            {
                root = nextKeyNode;
            }
            else
            {
                if (fatherOfDeletingNode->left == currentNode)
                {
                    fatherOfDeletingNode->left = nextKeyNode;
                }
                else
                {
                    fatherOfDeletingNode->right = nextKeyNode;
                }
            }
            if (tempNode == nextKeyNode)
            {
                nextKeyNode->right = currentNode;
            }
            else
            {
                nextKeyNode->right = tempNode;
                fatherOfSwapingNode->left = currentNode;
            }
            nextKeyNode->left = currentNode->left;
            currentNode->left = nullLeaf;
            nextKeyNode->color = deletingNodeColor;
            currentNode->color = swapingNodeColor;
            while (count > 0)
            {
                path->pop();
                count--;
            }
            path->push(nextKeyNode);
            tempNode = nextKeyNode->right;
            while (tempNode != currentNode)
            {
                path->push(tempNode);
                tempNode = tempNode->left;
            }
            Node<T, K> *childNode = currentNode->right;
            Node<T, K> *fatherNode = path->top();
            if (currentNode->left == nullLeaf && currentNode->right == nullLeaf && currentNode->color == Color::BLACK)
            {
                fixDeletion(currentNode, path);
            }
            if (fatherNode->left == currentNode)
            {
                fatherNode->left = childNode;
            }
            else
            {
                fatherNode->right = childNode;
            }
            if (childNode != nullLeaf)
            {
                childNode->color = Color::BLACK;
            }
        }
        delete currentNode;
        delete path;
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

    int getBlackHeight()
    {
        return getBlackHeightOfNode(root);
    }

    void clearTree()
    {
        deleteNode(root);
        root = nullLeaf;
    }
};
