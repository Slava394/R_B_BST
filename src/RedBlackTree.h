#pragma once
#include <functional>
#include "lab2/ArraySequence.h"
#include "../interface/IEnumerable.h"
#include "Stack.h"


template <typename T>
class RedBlackTree final : IEnumerable
{
private:
    //bool color enum for rb bst
    enum class Color : bool
    {
        RED,
        BLACK
    };
    //inner class which implement tree node
    class TreeNode
    {
    public:
        T key;
        Color color;
        TreeNode *left, *right, *parent;
        explicit TreeNode(const T &key,
                      const Color color,
                      TreeNode *left = nullptr,
                      TreeNode *right = nullptr,
                      TreeNode *parent = nullptr)
            : key(key), color(color), left(left), right(right), parent(parent) {}
    };
    //inner class iterator
    class TreeIterator final : public IEnumerator
    { //iterator for in-order
    private:
        TreeNode* current;
        TreeNode* nullLeaf;
        Stack<TreeNode*> stack{};

        void pushLeft(TreeNode* node)
        {
            while (node != nullLeaf)
            {
                stack.push(node);
                node = node->left;
            }
        }
    public:
        explicit TreeIterator(TreeNode *root, TreeNode *nullLeaf) : current(nullLeaf), nullLeaf(nullLeaf)
        {
            pushLeft(root);
            if (!stack.empty())
            {
                current = stack.pop();
            }
        }

        ~TreeIterator() override = default;

        bool operator==(const TreeIterator& other) const;

        bool operator!=(const TreeIterator& other) const;

        TreeIterator& operator++() override
        {
            if (current == nullLeaf)
            {
                throw std::out_of_range("It`s end iterator");
            }
            if (current->right != nullLeaf)
            {
                pushLeft(current->right);
            }
            if (stack.empty())
            {
                current = nullLeaf;
            }
            else
            {
                current = stack.pop();
            }
            return *this;
        }

        TreeIterator* operator++(int) override
        {
            auto *newIter = new TreeIterator(*this);
            ++(*this);
            return newIter;
        }

        TreeNode* operator->() const
        {
            return current;
        }

        TreeNode& operator*() const
        {
            return *current;
        }
    };
    //private fields
    TreeNode *root;
    TreeNode *nullLeaf;
    std::function<int(const T&, const T&)> comparator;
    //check color of the node
    bool isRed(TreeNode *node) const
    {
        return node != nullLeaf && node->color == Color::RED;
    }
    //check balance of the tree (5 properties of rb bst)
    bool checkRedProperties(TreeNode *node) const
    {
        if (node == nullLeaf && node->color == Color::RED)
        {
            std::cerr << "Null leaf isn`t black" << std::endl;
            return false; //property №2
        }
        if (node == nullLeaf && node->color == Color::BLACK)
        {
            return true;
        }
        if (node == root && node->color == Color::RED) //property №2
        {
            std::cerr << "Root isn`t black" << std::endl;
            return false;
        }
        if (isRed(node)) //property №3
        {
            if (isRed(node->left) || isRed(node->right))
            {
                std::cerr << "Red node with red child" << std::endl;
                return false;
            }
        }
        return checkRedProperties(node->left) && checkRedProperties(node->right); //recursion call
    }
    //check equality of all black heights and get result
    int checkBlackHeight(TreeNode *node) const
    {
        if (node == nullLeaf) return 1;
        int leftBlackHeight = checkBlackHeight(node->left);
        int rightBlackHeight = checkBlackHeight(node->right);
        if (leftBlackHeight == 0 || rightBlackHeight == 0 || leftBlackHeight != rightBlackHeight)
        {
            std::cerr << "Black height violation at node with key " << node->key << std::endl;
            return 0;
        }
        return leftBlackHeight + (node->color == Color::BLACK ? 1 : 0);
    }
    //left rotate in the tree
    void leftRotate(TreeNode *node)
    {
        TreeNode *rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullLeaf)
        {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr)
        {
            root = rightChild;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = rightChild;
        }
        else
        {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }
    //right rotate in the tree
    void rightRotate(TreeNode *node)
    {
        TreeNode *leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullLeaf)
        {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr)
        {
            root = leftChild;
        }
        else if (node == node->parent->left)
        {
            node->parent->left = leftChild;
        }
        else
        {
            node->parent->right = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }
    //balance fix after insertion
    void fixInsertion(TreeNode *newNode)
    {
        while (newNode != root && newNode->parent->color == Color::RED)
        {
            TreeNode *parent = newNode->parent;
            TreeNode *grandparent = parent->parent;
            if (parent == grandparent->left)
            {
                TreeNode *uncle = grandparent->right;
                if (uncle != nullLeaf && uncle->color == Color::RED)
                {
                    grandparent->color = Color::RED;
                    parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    newNode = grandparent;
                }
                else
                {
                    if (newNode == parent->right)
                    {
                        newNode->color = Color::BLACK;
                        leftRotate(parent);
                    }
                    else
                    {
                        parent->color = Color::BLACK;
                    }
                    grandparent->color = Color::RED;
                    rightRotate(grandparent);
                    break;
                }
            }
            else
            {
                TreeNode *uncle = grandparent->left;
                if (uncle != nullLeaf && uncle->color == Color::RED)
                {
                    grandparent->color = Color::RED;
                    parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    newNode = grandparent;
                }
                else
                {
                    if (newNode == parent->left)
                    {
                        newNode->color = Color::BLACK;
                        rightRotate(parent);
                    }
                    else
                    {
                        parent->color = Color::BLACK;
                    }
                    grandparent->color = Color::RED;
                    leftRotate(grandparent);
                    break;
                }
            }
        }
        root->color = Color::BLACK;
    }
    //balance fix after deletion
    void fixDeletion(TreeNode *child, TreeNode *parent)
    {
        while (child != root && child->color == Color::BLACK)
        {
            if (child == parent->left)
            {
                TreeNode *sibling = parent->right;
                if (sibling->color == Color::RED) //case №1 (red sibling)
                {
                    sibling->color = Color::BLACK;
                    parent->color = Color::RED;
                    leftRotate(parent);
                    sibling = parent->right;
                }
                if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK) //case №2 (black sibling)
                { //case №2.1 (black sibling right son, black sibiling left son)
                    sibling->color = Color::RED;
                    child = parent;
                    parent = child->parent;
                }
                else
                {
                    if (sibling->right->color == Color::BLACK) //case №2.2 (black sibling right son, red sibiling left son)
                    {
                        if (sibling->left != nullLeaf)
                        {
                            sibling->left->color = Color::BLACK;
                        }
                        sibling->color = Color::RED;
                        rightRotate(sibling);
                        sibling = parent->right;
                    }
                    sibling->color = parent->color; //case №2.3 (red sibling right son)
                    parent->color = Color::BLACK;
                    if (sibling->right != nullLeaf)
                    {
                        sibling->right->color = Color::BLACK;
                    }
                    leftRotate(parent);
                    break;
                }
            }
            else
            {
                TreeNode *sibling = parent->left;
                if (sibling->color == Color::RED)
                {
                    sibling->color = Color::BLACK;
                    parent->color = Color::RED;
                    rightRotate(parent);
                    sibling = parent->left;
                }
                if (sibling->left->color == Color::BLACK && sibling->right->color == Color::BLACK)
                {
                    sibling->color = Color::RED;
                    child = parent;
                    parent = child->parent;
                }
                else
                {
                    if (sibling->left->color == Color::BLACK)
                    {
                        if (sibling->right != nullLeaf)
                        {
                            sibling->right->color = Color::BLACK;
                        }
                        sibling->color = Color::RED;
                        leftRotate(sibling);
                        sibling = parent->left;
                    }

                    sibling->color = parent->color;
                    parent->color = Color::BLACK;
                    if (sibling->left != nullLeaf)
                    {
                        sibling->left->color = Color::BLACK;
                    }
                    rightRotate(parent);
                    break;
                }
            }
        }
        if (child != nullLeaf) //for lifting
        {
            child->color = Color::BLACK;
        }
    }
    //change of connection with children and parents at two nodes
    void swapNodes(TreeNode *firstNode, TreeNode *secondNode)
    {
        if (firstNode == secondNode)
        {
            return;
        }
        TreeNode *parent1 = firstNode->parent;
        TreeNode *parent2 = secondNode->parent;
        if (parent1 != nullptr)
        {
            if (parent1->left == firstNode)
            {
                parent1->left = secondNode;
            }
            else
            {
                parent1->right = secondNode;
            }
        }
        else
        {
            root = secondNode;
        }
        if (parent2 != nullptr)
        {
            if (parent2->left == secondNode)
            {
                parent2->left = firstNode;
            }
            else
            {
                parent2->right = firstNode;
            }
        }
        else
        {
            root = firstNode;
        }
        firstNode->parent = parent2;
        secondNode->parent = parent1;
        TreeNode *temp = firstNode->left;
        firstNode->left = secondNode->left;
        secondNode->left = temp;
        if (firstNode->left != nullLeaf)
        {
            firstNode->left->parent = firstNode;
        }
        if (secondNode->left != nullLeaf)
        {
            secondNode->left->parent = secondNode;
        }
        temp = firstNode->right;
        firstNode->right = secondNode->right;
        secondNode->right = temp;
        if (firstNode->right != nullLeaf)
        {
            firstNode->right->parent = firstNode;
        }
        if (secondNode->right != nullLeaf)
        {
            secondNode->right->parent = secondNode;
        }
        Color tempColor = firstNode->color;
        firstNode->color = secondNode->color;
        secondNode->color = tempColor;
    }
    //get the most left node
    TreeNode* getMostLeftNode(TreeNode *node)//for iterator
    {
        if (node == nullLeaf)
        {
            return nullLeaf;
        }
        while (node->left != nullLeaf)
        {
            node = node->left;
        }
        return node;
    }
    //help function for recursive deletion of the tree
    void deleteNode(TreeNode *node)
    {
        if (node != nullLeaf)
        {
            deleteNode(node->left);
            deleteNode(node->right);
            delete node;
        }
    }
    //user order method traversal
    void userOrderTraversalHelper(TreeNode *node, std::function<void(T&)> function,
        const int &leftNumber,
        const int &rightNumber,
        const int &rootNumber)
    {
        if (node != nullLeaf)
        {
            int count = 1;
            while (count != 4)
            {
                if (count == leftNumber)
                {
                    userOrderTraversalHelper(node->left, function, leftNumber, rightNumber, rootNumber);
                }
                else if (count == rightNumber)
                {
                    userOrderTraversalHelper(node->right, function, leftNumber, rightNumber, rootNumber);
                }
                else
                {
                    function(node->key);
                }
                ++count;
            }
        }
    }
    //user order traversal to save the tree as the string
    void userOrderToStringHelper(TreeNode *node, std::string &result,
    const int &leftNumber,
    const int &rightNumber,
    const int &rootNumber) const
    {
        if (node != nullLeaf)
        {
            int count = 1;
            while (count != 4)
            {
                if (count == leftNumber)
                {
                    userOrderToStringHelper(node->left, result, leftNumber, rightNumber, rootNumber);
                }
                else if (count == rightNumber)
                {
                    userOrderToStringHelper(node->right, result, leftNumber, rightNumber, rootNumber);
                }
                else
                {
                    updateResult(node->key, result);
                }
                ++count;
            }
        }
    }
    //update result
    void updateResult(T &nodeKey, std::string &result) const
    {
        result += "{" + std::to_string(nodeKey) + "}";
    }
    //for subtree search
    bool compareTrees(TreeNode *node1, TreeNode *node2, TreeNode *secondTreeNullLeaf) const
    {
        if (node1 == nullLeaf && node2 == secondTreeNullLeaf)
        {
            return true;
        }
        if (node1 == nullLeaf || node2 == secondTreeNullLeaf)
        {
            return false;
        }
        if (node1->key != node2->key)
        {
            return false;
        }
        //if non-null nodes with equal keys
        return compareTrees(node1->left, node2->left, secondTreeNullLeaf) &&
            compareTrees(node1->right, node2->right, secondTreeNullLeaf);
    }
    //extract help function
    void extractSubtreeHelper(TreeNode *node, RedBlackTree *result)
    {
        if (node != nullLeaf)
        {
            result->insertElement(node->key);
            extractSubtreeHelper(node->left, result);
            extractSubtreeHelper(node->right, result);
        }
    }
    //where help function
    void whereHelper(TreeNode *node, std::function<bool(T&)> predicate, RedBlackTree *result) const
    {
        if (node != nullLeaf)
        {
            if (predicate(node->key))
            {
                result->insertElement(node->key);
            }
            whereHelper(node->left, predicate, result);
            whereHelper(node->right, predicate, result);
        }
    }
    //reduce help function
    void reduceHelper(TreeNode *node, T& result, std::function<T(const T&, const T&)> function) const
    {
        if (node != nullLeaf)
        {
            reduceHelper(node->left, result, function);
            result = function(result, node->key);
            reduceHelper(node->right, result, function);
        }
    }
    //for pretty number output
    void fillLevels(MutableArraySequence<MutableArraySequence<TreeNode*>*> &levels)
    {   //non-recursion fill sequense of sequence pointe holding node pointer
        levels.Append(new MutableArraySequence<TreeNode*>());
        levels[0]->Append(root);
        int currentLevel = 0;
        while (currentLevel < levels.GetLength()) {
            MutableArraySequence<TreeNode*> *current = levels[currentLevel];
            auto *nextLevel = new MutableArraySequence<TreeNode*>();
            bool hasValidNode = false;
            for (int index{0}; index < current->GetLength(); ++index)
            {
                TreeNode *node = current->Get(index);
                if (node != nullLeaf)
                {
                    hasValidNode = true;
                    nextLevel->Append(node->left);
                    nextLevel->Append(node->right);
                }
                else
                {
                    nextLevel->Append(nullLeaf);
                    nextLevel->Append(nullLeaf);
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
    //get number length
    template <typename K>
    [[nodiscard]] static int getNumberWidth(K number)
    {   //get number width
        int width = 0;
        while (number != 0)
        {
            number /= 10;
            width++;
        }
        return width;
    }
    //print help function
    void printHelper(TreeNode *node, std::string indent, bool last) const
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
public:
    //constructor need a comparator for the key type
    explicit RedBlackTree(std::function<int(const T&,const T&)> comparator)
    {
        this->comparator = comparator;
        nullLeaf = new TreeNode(T(), Color::BLACK);
        root = nullLeaf;
    }
    //destructor
    ~RedBlackTree() override
    {
        clear();
        delete nullLeaf;
    }
    //user order method traversal
    void traverse(const std::string &order, std::function<void(T&)> function)
    {
        if (order == "LRN")
        {
            userOrderTraversalHelper(root, function, 1, 2, 3);
        }
        else if (order == "LNR")
        {
            userOrderTraversalHelper(root, function, 1, 3, 2);
        }
        else if (order == "NLR")
        {
            userOrderTraversalHelper(root, function, 2, 3, 1);
        }
        else if (order == "NRL")
        {
            userOrderTraversalHelper(root, function, 3, 2, 1);
        }
        else if (order == "RLN")
        {
            userOrderTraversalHelper(root, function, 2, 1, 3);
        }
        else if (order == "RNL")
        {
            userOrderTraversalHelper(root, function, 3, 1, 2);
        }
        else
        {
            std::cerr << "Unknown traversal order" << std::endl;
        }
    }
    //save as a string with choose type of traversal
    [[nodiscard]] std::string saveToString(const std::string &order) const
    {
        std::string result;
        if (order == "LRN")
        {
            userOrderToStringHelper(root, result, 1, 2, 3);
        }
        else if (order == "LNR")
        {
            userOrderToStringHelper(root, result, 1, 3, 2);
        }
        else if (order == "NLR")
        {
            userOrderToStringHelper(root, result, 2, 3, 1);
        }
        else if (order == "NRL")
        {
            userOrderToStringHelper(root, result, 3, 2, 1);
        }
        else if (order == "RLN")
        {
            userOrderToStringHelper(root, result, 2, 1, 3);
        }
        else if (order == "RNL")
        {
            userOrderToStringHelper(root, result, 3, 1, 2);
        }
        else
        {
            std::cerr << "Unknown traversal order" << std::endl;
        }
        return "(" + order + ")" + result;
    }
    //insertion
    void insertElement(const T &key)
    {
        auto *newNode = new TreeNode(key, Color::RED, nullLeaf, nullLeaf);
        TreeNode *currentNode = root;
        TreeNode *parent = nullptr;
        while (currentNode != nullLeaf)
        {
            parent = currentNode;
            if (comparator(currentNode->key, key) == 1)
            {
                currentNode = currentNode->right;
            }
            else if (comparator(currentNode->key, key) == -1)
            {
                currentNode = currentNode->left;
            }
            else
            { //duplicate case
                delete newNode;
                return;
            }
        }
        newNode->parent = parent;
        if (parent == nullptr)
        {
            root = newNode;
        }
        else if (comparator(parent->key, key) == 1)
        {
            parent->right = newNode;
        }
        else
        {
            parent->left = newNode;
        }
        fixInsertion(newNode);
    }
    //search by key
    TreeNode *searchElement(const T &key) const
    {
        TreeNode *currentNode = root;
        while (currentNode != nullLeaf && comparator(currentNode->key, key) != 0)
        {
            if (comparator(currentNode->key, key) == 1)
            {
                currentNode = currentNode->right;
            }
            else if (comparator(currentNode->key, key) == -1)
            {
                currentNode = currentNode->left;
            }
        }
        return currentNode == nullLeaf ? nullptr : currentNode;
    }
    //deletion by key
    void deleteElement(const T &key)
    {
        TreeNode *currentNode = root;
        TreeNode *parent = nullptr;
        while (currentNode != nullLeaf && comparator(currentNode->key, key) != 0)
        {
            parent = currentNode;
            if (comparator(currentNode->key, key) == 1)
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
            return;
        }
        if (currentNode->left != nullLeaf && currentNode->right != nullLeaf)
        {
            TreeNode *receiver = currentNode->right;
            parent = receiver;
            while (receiver->left != nullLeaf)
            {
                parent = receiver;
                receiver = receiver->left;
            }
            swapNodes(currentNode, receiver);
        }
        TreeNode *childNode = currentNode->left == nullLeaf ? currentNode->right : currentNode->left;
        if (currentNode == root)
        {
            root = childNode;
        }
        else
        {
            if (parent != nullptr)
            {
                if (parent->left == currentNode)
                {
                    parent->left = childNode;
                }
                else
                {
                    parent->right = childNode;
                }
            }
        }
        if (childNode != nullLeaf)
        {
            childNode->parent = parent;
        }
        if (currentNode->color == Color::BLACK)
        {
            fixDeletion(childNode, parent);
        }
        delete currentNode;
    }
    //subtree search
    TreeNode* searchSubtree(RedBlackTree *otherRbt)
    {
        TreeNode *target = searchElement(otherRbt->root->key);
        if (target == nullptr) return nullptr;
        return (compareTrees(target, otherRbt->root, otherRbt->nullLeaf) ?
            searchElement(otherRbt->root->key) : nullptr);
    }
    //subtree extraction
    RedBlackTree* extractSubtree(const T &key)
    {
        TreeNode *target = searchElement(key);
        auto *result = new RedBlackTree(comparator);
        if (target == nullptr) return result;
        extractSubtreeHelper(target, result);
        return result;
    }
    //map
    RedBlackTree* map(std::function<void(T&)> function)
    {
        userOrderTraversalHelper(root, function, 2, 3, 1);
        return this;
    }
    //where
    RedBlackTree* where(std::function<bool(T&)> predicate)
    {
        auto *result = new RedBlackTree(comparator);
        whereHelper(root, predicate, result);
        return result;
    }
    //reduce
    T reduce(const T &initialValue, std::function<T(const T&, const T&)> function)
    {
        T result = initialValue;
        reduceHelper(root, result, function);
        return result;
    }
    //for red-black balance checking
    [[nodiscard]] int getBlackHeight() const
    {
        return checkBlackHeight(root);
    }
    //for red-black properties check
    [[nodiscard]] bool checkBalance() const
    {
        return checkRedProperties(root);
    }
    //in-oreder iterator - begin
    TreeIterator* begin() override
    {
        return new TreeIterator(root, nullLeaf);
    }
    //in-oreder iterator - end (nullLeaf)
    TreeIterator* end() override
    {
        return new TreeIterator(nullLeaf, nullLeaf);
    }
    //clear tree
    void clear()
    {
        deleteNode(root);
        root = nullLeaf;
    }
    //tree print (as a tree)
    void printTree() const
    {
        if (root)
        {
            printHelper(root, "", true);
        }
    }
    //beautiful tree print but only for number (0> and <1000 or break smth)
    void beautifulPrintTree()
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
};
