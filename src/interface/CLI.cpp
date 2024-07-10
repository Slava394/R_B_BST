#include <iostream>
#include <sstream>
#include <readline/readline.h>
#include <readline/history.h>
#include <functional>
#include "CLI.h"
#include "../lab2/ArraySequence.h"
#include "../lab4/RedBlackTree.h"
#include "../lab4/PrintFunction.h"


int standardComparator(const long &left, const long &right)
{
    if (left < right)
    {
        return 1;
    }
    if (left > right)
    {
        return -1;
    }
    return 0;
}

struct NamedTree
{
public:
    std::string name;
    RedBlackTree<long> *tree;
    NamedTree(std::string name, RedBlackTree<long> *tree) : name(std::move(name)), tree(tree) {}
};
//get a tree by name
NamedTree *findTreeByName(MutableArraySequence<NamedTree*> &trees, std::string &name)
{
    NamedTree *namedTree = nullptr;
    for (int index{0}; index < trees.GetLength(); ++index)
    {
        if (trees.Get(index)->name == name)
        {
            namedTree = trees.Get(index);
        }
    }
    return namedTree;
}
//print tree (inorder)
void print(const NamedTree *namedTree)
{
    std::cout << namedTree->name << ":" << std::endl;
    namedTree->tree->traverse("LNR", [](const long &key){ std::cout << key << " "; });
    std::cout << std::endl;
}
//beautiful print
void beautyPrint(const NamedTree *namedTree)
{
    std::cout << namedTree->name << ":" << std::endl;
    beautifulPrintTree(namedTree->tree);
}
//create a named tree
void createTree(MutableArraySequence<NamedTree*> &trees, std::istringstream &stringStream)
{
    std::string name;
    stringStream >> name;
    if (name.empty())
    {
        std::cerr << "Error: Missing name for tree creation" << std::endl;
        return;
    }
    NamedTree *namedTree = findTreeByName(trees, name);
    if (namedTree == nullptr)
    {
        long argument;
        auto *tree = new RedBlackTree<long>(standardComparator);
        while (stringStream >> argument)
        {
            tree->insertElement(argument);
        }
        try
        {
            namedTree = new NamedTree(name, tree);
        }
        catch (...)
        {
            delete tree;
            std::cerr << "Error: Failed to create tree" << name << std::endl;
            return;
        }
        trees.Append(namedTree);
        print(namedTree);
    }
    else
    {
        std::cerr << "Error: Tree " << name << " already exist" << std::endl;
    }
}
//handle exception in the interface
template <typename functionType, typename ...argumentType>
void handleExceptions(functionType function, argumentType &&...args)
{
    try
    {
        function(std::forward<argumentType>(args)...);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
//insertion element
void insert(NamedTree *namedTree, std::istringstream &stringStream)
{
    long key;
    int count = 0;
    while (stringStream >> key)
    {
        namedTree->tree->insertElement(key);
        ++count;
    }
    if (count > 0) { print(namedTree); return; }
    else { std::cerr << "Error: Missing key for element insertion" << std::endl; }
}
//search element
void searchElement(NamedTree *namedTree, std::istringstream &stringStream)
{
    long key;
    if (stringStream >> key)
    {
        if (namedTree->tree->searchElement(key))
        {
            std::cout << "Element " << key << " was found in this tree" << std::endl;
        }
        else
        {
            std::cout << "Element " << key << " was not found in this tree" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Missing key for element search" << std::endl;
    }
}
//search subtree
void searchSubtree(NamedTree *namedTree,
                   MutableArraySequence<NamedTree*> &trees,
                   std::istringstream &stringStream)
{
    std::string otherTreeName;
    if (stringStream >> otherTreeName)
    {
        NamedTree *otherTree = findTreeByName(trees, otherTreeName);
        if (otherTree)
        {
            auto *result = namedTree->tree->searchSubtree(otherTree->tree);
            if (result)
            {
                std::cout << "Subtree was found in this tree" << std::endl;
            }
            else
            {
                std::cout << "Subtree was not found in this tree" << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Tree " << otherTreeName << " not found" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Missing tree for subtree search" << std::endl;
    }
}
//deletion element
void delete1(NamedTree *namedTree, std::istringstream &stringStream)
{
    long key;
    int count = 0;
    while (stringStream >> key)
    {
        namedTree->tree->deleteElement(key);
        ++count;
    }
    if (count > 0) { print(namedTree); return; }
    else { std::cerr << "Error: Missing key for element deletion" << std::endl; }
}
//extract
void extract(NamedTree *namedTree, std::istringstream &stringStream)
{
    long key;
    if (stringStream >> key)
    {
        if (namedTree->tree->searchElement(key))
        {
            auto *result = namedTree->tree->extractSubtree(key);
            std::cout << "Subtree was found:" << std::endl;
            result->traverse("LNR", [](const long &key){ std::cout << key << " "; });
            std::cout << std::endl;
            delete result;
        }
        else
        {
            std::cout << "Element " << key << " was not found in this tree" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Missing key for subtree extraction" << std::endl;
    }
}
//clear the tree
void clear(NamedTree *namedTree)
{
    namedTree->tree->clear();
    std::cout << "Tree " << namedTree->name << " was cleaned" << std::endl;
}
//print tree names
void printAll(const MutableArraySequence<NamedTree*> &trees)
{
    std::cout << "List of all trees:" <<std::endl;
    for (int index{0}; index < trees.GetLength(); ++index)
    {
        std::cout << trees.Get(index)->name << " ";
    }
    std::cout << std::endl;
}
//map
void map(NamedTree *namedTree, std::istringstream &stringStream)
{
    std::string functionName;
    if (stringStream >> functionName)
    {
        if (functionName == "*3")
        {
            namedTree->tree->map([](long &x) { return x *= 3; });
        }
        else if (functionName == "-50")
        {
            namedTree->tree->map([](long &x) { return x -= 50; });
        }
        else if (functionName == "+7")
        {
            namedTree->tree->map([](long &x) { return x += 7; });
        }
        else
        {
            std::cerr << "Error: Invalid function name " << functionName << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "Missing function name for map" << std::endl;
        return;
    }
    print(namedTree);
}
//reduce
void reduce(NamedTree *namedTree, std::istringstream &stringStream)
{
    std::string functionName;
    long result;
    if (stringStream >> functionName)
    {
        if (functionName == "+")
        {
            result = namedTree->tree->reduce(10, [](const long &a, const long &b) { return a + b; });
        }
        else if (functionName == "-")
        {
            result = namedTree->tree->reduce(10, [](const long &a, const long &b) { return a - b; });
        }
        else if (functionName == "*")
        {
            result = namedTree->tree->reduce(10, [](const long &a, const long &b) { return a * b; });
        }
        else
        {
            std::cerr << "Error: Invalid function name " << functionName << std::endl;
            return;
        }
    }
    else
    {
        std::cerr << "Missing function name for reduce" << std::endl;
        return;
    }
    std::cout << "Reduce <" << functionName << "> result of the tree:" << std::endl << result <<std::endl;
}
//to string
void toString(NamedTree *namedTree, std::istringstream &stringStream)
{
    std::string traversalOrder;
    if (stringStream >> traversalOrder)
    {
        std::cout << "Tree as a string :" << std::endl << namedTree->tree->saveToString(traversalOrder) << std::endl;
    }
    else
    {
        std::cerr << "Error: Missing order for traversal" << std::endl;
    }
}
//user order traversal
void traverse(NamedTree *namedTree, std::istringstream &stringStream)
{
    std::string traversalOrder, functionName;
    if (stringStream >> functionName)
    {
        if (functionName == "print")
        {
            if (stringStream >> traversalOrder)
            {
                namedTree->tree->traverse(traversalOrder, [](long &x){ std::cout << x << " "; });
                std::cout << std::endl;
            }
            else
            {
                std::cerr << "Error: Missing order for traversal" << std::endl;
            }
        }
        else if (functionName == "*2")
        {
            if (stringStream >> traversalOrder)
            {
                namedTree->tree->traverse(traversalOrder, [](long &x){ x *= 2; });
                print(namedTree);
            }
            else
            {
                std::cerr << "Error: Missing order for traversal" << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Invalid function name " << functionName << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Missing function name for traversal" << std::endl;
    }
}
//where
void where(NamedTree *namedTree, std::istringstream &stringStream)
{
    std::string filterName;
    if (stringStream >> filterName)
    {
        if (filterName == "even")
        {
            auto *result = namedTree->tree->where([](const long &x){ return x % 2 == 0; });
            std::cout << "Filtered tree:" << std::endl;
            result->traverse("LNR", [](const long &key){ std::cout << key << " "; });
            std::cout << std::endl;
            delete result;
        }
        else if (filterName == "odd")
        {
            auto *result = namedTree->tree->where([](const long &x){ return x % 2 == 1; });
            std::cout << "Filtered tree:" << std::endl;
            result->traverse("LNR", [](const long &key){ std::cout << key << " "; });
            std::cout << std::endl;
            delete result;
        }
        else
        {
            std::cerr << "Error: Invalid filter name " << filterName << std::endl;
        }
    }
    else
    {
        std::cerr << "Error: Missing filter name for where" << std::endl;
    }
}
//print the list of commands
void help()
{
    std::cout << "Tree Methods:\n"
         << "  create <name> <optional args>: Create a tree with the given name and elements.\n"
         << "  print <name>: Print the tree in an orderly manner.\n"
         << "  print_all: Print all tree names.\n"
         << "  insert <name> <key>: Insert an element with the given key.\n"
         << "  search_element <name> <key>: Search for an element by key.\n"
         << "  search_subtree <name> <other tree name>: Search for an subtree.\n"
         << "  delete <name> <key>: Delete an element with the given key.\n"
         << "  clear <name>: Delete all element of the tree.\n"
         << "  extract <name> <key>: Extract an subtree by key and print it.\n" //done
         << "  beauty_print <name>: Beautifully print a random tree.\n" //done
         << "  map <name> [*3 | -50 | +7]: Apply a function to each element of the tree.\n"
         << "  where <name> [even | odd]: Filter tree elements by condition.\n"
         << "  reduce <name> [+ | - | *]: Reduce tree elements by the given operation with initial value 10.\n"
         << "  to_string <name> <traversal order>: Convert the tree to a string in the given traversal order.\n"
         << "  traverse <name> [print | *2] <traversal order>: Traverse the tree and apply an operation.\n"
         << "  exit: Exit the program.\n"
         << "P.S.: traversal order in the form for example 'RLN', where R - right, L - left and N - node (root).\n";
}

void CLI()
{
    MutableArraySequence<NamedTree*> trees;
    std::string line, command, name;
    std::cout << "Red black tree CLI\nType \"help\" for more information.\n";
    while (true)
    {
        line.clear();
        command.clear();
        name.clear();
        char *input = readline(">>> ");
        if (input == nullptr)
        {
            break;
        }
        line = std::string(input);
        if (line.empty())
        {
            continue;
        }
        add_history(line.c_str());
        free(input);
        std::istringstream stringStream{line};
        stringStream >> command;
        if (command == "create")
        {
            handleExceptions<void(MutableArraySequence<NamedTree*>&,
                    std::istringstream&)>(createTree, trees, stringStream);
        }
        else if (command == "print")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(const NamedTree*)>(print, namedTree); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "beauty_print")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(const NamedTree*)>(beautyPrint, namedTree); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "print_all")
        {
            handleExceptions<void(const MutableArraySequence<NamedTree*>&)>(printAll, trees);
        }
        else if (command == "insert")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*, std::istringstream&)>(insert, namedTree, stringStream); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "delete")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*, std::istringstream&)>(delete1, namedTree, stringStream); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "search_element")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*, std::istringstream&)>(searchElement, namedTree, stringStream); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "search_subtree")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*, MutableArraySequence<NamedTree*>&, std::istringstream&)>
                    (searchSubtree, namedTree, trees, stringStream); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "clear")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*)>(clear, namedTree); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "map")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*, std::istringstream&)>(map, namedTree, stringStream); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "where")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*, std::istringstream&)>(where, namedTree, stringStream); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "reduce")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*, std::istringstream&)>(reduce, namedTree, stringStream); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "to_string")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*, std::istringstream&)>(toString, namedTree, stringStream); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "traverse")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(NamedTree*, std::istringstream&)>(traverse, namedTree, stringStream); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "beauty_print")
        {
            if (!(stringStream >> name)) { std::cerr << "Error: Missing tree name" << std::endl; continue; }
            NamedTree *namedTree = findTreeByName(trees, name);
            if (namedTree) { handleExceptions<void(const NamedTree*)>(beautyPrint, namedTree); }
            else { std::cerr << "Error: Tree " << name << " not found" << std::endl; continue; }
        }
        else if (command == "exit")
        {
            std::cout << "Goodbye" << std::endl;
            break;
        }
        else if (command == "help")
        {
            help();
        }
        else
        {
            std::cerr << "Error: Unknown command" << std::endl;
        }
    }
    for (int index{0}; index < trees.GetLength(); ++index)
    {
        delete trees.Get(index)->tree;
        delete trees.Get(index);
    }
}
