#include <iostream>
#include <cassert>
#include <complex>
#include <vector>
#include <climits>
#include <random>
#include <chrono>
#include "../src/lab4/RedBlackTree.h"
#include "RedBlackTreeTest.h"


int standardLongComparator(const long &a, const long &b)
{
    if (a < b) return 1;
    if (a > b) return -1;
    return 0;
}

int standardComplexComparator(const std::complex<long> &a, const std::complex<long> &b)
{
    if (a.real() < b.real()) return 1;
    if (a.real() > b.real()) return -1;
    if (a.imag() < b.imag()) return 1;
    if (a.imag() > b.imag()) return -1;
    return 0;
}

void TestInsertLong()
{
    auto *tree = new RedBlackTree<long>(standardLongComparator);
    {
        tree->insertElement(10);
        tree->insertElement(10);
        assert(tree->searchElement(10) != nullptr);
    }
    {
        for (long index = 1; index <= 5; ++index)
        {
            tree->insertElement(index);
        }
        for (long index = 1; index <= 5; ++index)
        {
            assert(tree->searchElement(index) != nullptr);
        }
    }
    {
        for (long index = 10; index >= 6; --index)
        {
            tree->insertElement(index);
        }
        for (long index = 6; index <= 10; ++index)
        {
            assert(tree->searchElement(index) != nullptr);
        }
    }
    {
        tree->insertElement(11);
        tree->insertElement(12);
        tree->insertElement(15);
        tree->deleteElement(12);
        tree->deleteElement(15);
        assert(tree->searchElement(12) == nullptr);
        assert(tree->searchElement(15) == nullptr);
        assert(tree->searchElement(11) != nullptr);
    }
    delete tree;
    std::cout << "[PASSED] testInsertLong" << std::endl;
}

void TestInsertComplex()
{
    auto *tree = new RedBlackTree<std::complex<long>>(standardComplexComparator);
    {
        std::complex<long> complexNumber1(3, 4);
        std::complex<long> complexNumber2(3, 4);
        tree->insertElement(complexNumber1);
        tree->insertElement(complexNumber2);
        assert(tree->searchElement(complexNumber1) != nullptr);
    }
    {
        std::complex<long> complexNumber1(1, 2);
        std::complex<long> complexNumber2(2, 3);
        std::complex<long> complexNumber3(3, 4);
        tree->insertElement(complexNumber1);
        tree->insertElement(complexNumber2);
        tree->insertElement(complexNumber3);
        assert(tree->searchElement(complexNumber1) != nullptr);
        assert(tree->searchElement(complexNumber2) != nullptr);
        assert(tree->searchElement(complexNumber3) != nullptr);
    }
    {
        std::complex<long> complexNumber(1, 2);
        tree->deleteElement(complexNumber);
        assert(tree->searchElement(complexNumber) == nullptr);
    }
    delete tree;
    std::cout << "[PASSED] testInsertComplex" << std::endl;
}

void TestDeleteLong()
{
    auto *tree = new RedBlackTree<long>(standardLongComparator);
    {
        tree->insertElement(10);
        tree->deleteElement(10);
        assert(tree->searchElement(10) == nullptr);
    }
    {
        tree->insertElement(10);
        tree->insertElement(5);
        tree->insertElement(15);
        tree->deleteElement(10);
        assert(tree->searchElement(10) == nullptr);
        assert(tree->searchElement(5) != nullptr);
        assert(tree->searchElement(15) != nullptr);
    }
    {
        tree->insertElement(20);
        tree->insertElement(25);
        tree->deleteElement(20);
        assert(tree->searchElement(20) == nullptr);
        assert(tree->searchElement(25) != nullptr);
    }
    {
        tree->insertElement(10);
        tree->insertElement(5);
        tree->insertElement(15);
        tree->insertElement(2);
        tree->insertElement(7);
        tree->deleteElement(5);
        assert(tree->searchElement(5) == nullptr);
        assert(tree->searchElement(2) != nullptr);
        assert(tree->searchElement(7) != nullptr);
    }
    delete tree;
    std::cout << "[PASSED] TestDeleteLong" << std::endl;
}

void TestDeleteComplex()
{
    auto *tree = new RedBlackTree<std::complex<long>>(standardComplexComparator);
    {
        std::complex<long> complexNumber(3, 4);
        tree->insertElement(complexNumber);
        tree->deleteElement(complexNumber);
        assert(tree->searchElement(complexNumber) == nullptr);
    }
    {
        std::complex<long> complexNumber1(3, 4);
        std::complex<long> complexNumber2(1, 2);
        std::complex<long> complexNumber3(5, 6);
        tree->insertElement(complexNumber1);
        tree->insertElement(complexNumber2);
        tree->insertElement(complexNumber3);
        tree->deleteElement(complexNumber1);
        assert(tree->searchElement(complexNumber1) == nullptr);
        assert(tree->searchElement(complexNumber2) != nullptr);
        assert(tree->searchElement(complexNumber3) != nullptr);
    }
    {
        std::complex<long> complexNumber1(10, 20);
        std::complex<long> complexNumber2(15, 25);
        tree->insertElement(complexNumber1);
        tree->insertElement(complexNumber2);
        tree->deleteElement(complexNumber1);
        assert(tree->searchElement(complexNumber1) == nullptr);
        assert(tree->searchElement(complexNumber2) != nullptr);
    }
    {
        std::complex<long> complexNumber1(1, 2);
        std::complex<long> complexNumber2(0, 1);
        std::complex<long> complexNumber3(2, 3);
        std::complex<long> complexNumber4(1, 1);
        std::complex<long> complexNumber5(1, 3);
        tree->insertElement(complexNumber1);
        tree->insertElement(complexNumber2);
        tree->insertElement(complexNumber3);
        tree->insertElement(complexNumber4);
        tree->insertElement(complexNumber5);
        tree->deleteElement(complexNumber1);
        assert(tree->searchElement(complexNumber1) == nullptr);
        assert(tree->searchElement(complexNumber2) != nullptr);
        assert(tree->searchElement(complexNumber3) != nullptr);
        assert(tree->searchElement(complexNumber4) != nullptr);
        assert(tree->searchElement(complexNumber5) != nullptr);
    }
    delete tree;
    std::cout << "[PASSED] TestDeleteComplex" << std::endl;
}

void TestSearchLong()
{
    auto *tree = new RedBlackTree<long>(standardLongComparator);
    {
        assert(tree->searchElement(10) == nullptr);
    }
    {
        tree->insertElement(10);
        assert(tree->searchElement(10) != nullptr);
        assert(tree->searchElement(5) == nullptr);
    }
    {
        tree->insertElement(20);
        tree->insertElement(15);
        tree->insertElement(25);
        assert(tree->searchElement(10) != nullptr);
        assert(tree->searchElement(20) != nullptr);
        assert(tree->searchElement(15) != nullptr);
        assert(tree->searchElement(25) != nullptr);
        assert(tree->searchElement(5) == nullptr);
        assert(tree->searchElement(30) == nullptr);
    }
    delete tree;
    std::cout << "[PASSED] TestSearchLong" << std::endl;
}

void TestSearchComplex()
{
    auto *tree = new RedBlackTree<std::complex<long>>(standardComplexComparator);
    {
        std::complex<long> complexNumber(3, 4);
        assert(tree->searchElement(complexNumber) == nullptr);
    }
    {
        std::complex<long> complexNumber(3, 4);
        tree->insertElement(complexNumber);
        assert(tree->searchElement(complexNumber) != nullptr);
        std::complex<long> nonExistentNumber(1, 2);
        assert(tree->searchElement(nonExistentNumber) == nullptr);
    }
    {
        std::complex<long> complexNumber1(3, 4);
        std::complex<long> complexNumber2(1, 2);
        std::complex<long> complexNumber3(5, 6);
        tree->insertElement(complexNumber2);
        tree->insertElement(complexNumber3);
        assert(tree->searchElement(complexNumber1) != nullptr);
        assert(tree->searchElement(complexNumber2) != nullptr);
        assert(tree->searchElement(complexNumber3) != nullptr);
        std::complex<long> nonExistentNumber1(0, 0);
        std::complex<long> nonExistentNumber2(6, 7);
        assert(tree->searchElement(nonExistentNumber1) == nullptr);
        assert(tree->searchElement(nonExistentNumber2) == nullptr);
    }
    delete tree;
    std::cout << "[PASSED] TestSearchComplex" << std::endl;
}

void TestMapLong()
{
    auto *tree = new RedBlackTree<long>(standardLongComparator);
    {
        auto increment = [](long &value) { value += 1; };
        tree->map(increment);
        assert(tree->searchElement(1) == nullptr);
    }
    {
        tree->insertElement(5);
        auto increment = [](long &value) { value += 1; };
        tree->map(increment);
        assert(tree->searchElement(5) == nullptr);
        assert(tree->searchElement(6) != nullptr);
    }
    {
        tree->insertElement(10);
        tree->insertElement(15);
        tree->insertElement(20);
        auto increment = [](long &value) { value += 1; };
        tree->map(increment);
        assert(tree->searchElement(10) == nullptr);
        assert(tree->searchElement(11) != nullptr);
        assert(tree->searchElement(15) == nullptr);
        assert(tree->searchElement(16) != nullptr);
        assert(tree->searchElement(20) == nullptr);
        assert(tree->searchElement(21) != nullptr);
    }
    delete tree;
    std::cout << "[PASSED] TestMapLong" << std::endl;
}

void TestMapComplex()
{
    auto *tree = new RedBlackTree<std::complex<long>>(standardComplexComparator);
    {
        auto increment = [](std::complex<long> &value) { value += std::complex<long>(1, 1); };
        tree->map(increment);
        std::complex<long> complexNumber(1, 1);
        assert(tree->searchElement(complexNumber) == nullptr);
    }
    {
        std::complex<long> complexNumber(2, 3);
        tree->insertElement(complexNumber);
        auto increment = [](std::complex<long> &value) { value += std::complex<long>(1, 1); };
        tree->map(increment);
        assert(tree->searchElement(complexNumber) == nullptr);
        std::complex<long> incrementedComplexNumber(3, 4);
        assert(tree->searchElement(incrementedComplexNumber) != nullptr);
    }
    {
        std::complex<long> complexNumber1(4, 5);
        std::complex<long> complexNumber2(6, 7);
        std::complex<long> complexNumber3(8, 9);
        tree->insertElement(complexNumber1);
        tree->insertElement(complexNumber2);
        tree->insertElement(complexNumber3);
        auto increment = [](std::complex<long> &value) { value += std::complex<long>(1, 1); };
        tree->map(increment);
        assert(tree->searchElement(std::complex<long>(5, 6)) != nullptr);
        assert(tree->searchElement(std::complex<long>(7, 8)) != nullptr);
        assert(tree->searchElement(std::complex<long>(9, 10)) != nullptr);
    }
    delete tree;
    std::cout << "[PASSED] TestMapComplex" << std::endl;
}

void TestWhereLong()
{
    auto *tree = new RedBlackTree<long>(standardLongComparator);
    {
        auto isEven = [](long &value) { return value % 2 == 0; };
        RedBlackTree<long> *filteredTree = tree->where(isEven);
        assert(filteredTree->searchElement(2) == nullptr);
        delete filteredTree;
    }
    {
        tree->insertElement(5);
        auto isEven = [](long &value) { return value % 2 == 0; };
        RedBlackTree<long> *filteredTree = tree->where(isEven);
        assert(filteredTree->searchElement(5) == nullptr);
        delete filteredTree;
    }
    {
        tree->insertElement(10);
        tree->insertElement(15);
        tree->insertElement(20);
        auto isEven = [](long &value) { return value % 2 == 0; };
        RedBlackTree<long> *filteredTree = tree->where(isEven);
        assert(filteredTree->searchElement(10) != nullptr);
        assert(filteredTree->searchElement(15) == nullptr);
        assert(filteredTree->searchElement(20) != nullptr);
        delete filteredTree;
    }
    {
        auto isOdd = [](long &value) { return value % 2 != 0; };
        RedBlackTree<long> *filteredTree = tree->where(isOdd);
        assert(filteredTree->searchElement(5) != nullptr);
        assert(filteredTree->searchElement(10) == nullptr);
        assert(filteredTree->searchElement(15) != nullptr);
        assert(filteredTree->searchElement(20) == nullptr);
        delete filteredTree;
    }
    delete tree;
    std::cout << "[PASSED] TestWhereLong" << std::endl;
}

void TestWhereComplex()
{
    auto *tree = new RedBlackTree<std::complex<long>>(standardComplexComparator);
    {
        auto isRealPositive = [](std::complex<long> &value) { return value.real() > 0; };
        RedBlackTree<std::complex<long>> *filteredTree = tree->where(isRealPositive);
        std::complex<long> complexNumber(1, 1);
        assert(filteredTree->searchElement(complexNumber) == nullptr);
        delete filteredTree;
    }
    {
        std::complex<long> complexNumber(2, 3);
        tree->insertElement(complexNumber);
        auto isRealPositive = [](std::complex<long> &value) { return value.real() > 0; };
        RedBlackTree<std::complex<long>> *filteredTree = tree->where(isRealPositive);
        assert(filteredTree->searchElement(complexNumber) != nullptr);
        delete filteredTree;
    }
    {
        std::complex<long> complexNumber1(4, 5);
        std::complex<long> complexNumber2(-6, 7);
        std::complex<long> complexNumber3(8, -9);
        tree->insertElement(complexNumber1);
        tree->insertElement(complexNumber2);
        tree->insertElement(complexNumber3);
        auto isRealPositive = [](std::complex<long> &value) { return value.real() > 0; };
        RedBlackTree<std::complex<long>> *filteredTree = tree->where(isRealPositive);
        assert(filteredTree->searchElement(complexNumber1) != nullptr);
        assert(filteredTree->searchElement(complexNumber2) == nullptr);
        assert(filteredTree->searchElement(complexNumber3) != nullptr);
        delete filteredTree;
    }
    {
        auto isImagNegative = [](std::complex<long> &value) { return value.imag() < 0; };
        RedBlackTree<std::complex<long>> *filteredTree = tree->where(isImagNegative);
        assert(filteredTree->searchElement(std::complex<long>(4, 5)) == nullptr);
        assert(filteredTree->searchElement(std::complex<long>(-6, 7)) == nullptr);
        assert(filteredTree->searchElement(std::complex<long>(8, -9)) != nullptr);
        delete filteredTree;
    }
    delete tree;
    std::cout << "[PASSED] TestWhereComplex" << std::endl;
}

void TestReduceLong()
{
    auto *tree = new RedBlackTree<long>(standardLongComparator);
    tree->insertElement(10);
    tree->insertElement(20);
    tree->insertElement(30);
    {
        auto sumFunction = [](const long &a, const long &b) { return a + b; };
        long sum = tree->reduce(0, sumFunction);
        assert(sum == 60);
    }
    {
        auto maxFunction = [](const long &a, const long &b) { return (a > b) ? a : b; };
        long max = tree->reduce(LONG_MIN, maxFunction);
        assert(max == 30);
    }
    delete tree;
    std::cout << "[PASSED] TestReduceLong" << std::endl;
}

void TestReduceComplex()
{
    auto *tree = new RedBlackTree<std::complex<long>>(standardComplexComparator);
    std::complex<long> complexNumber1(1, 2);
    std::complex<long> complexNumber2(3, 4);
    std::complex<long> complexNumber3(5, 6);
    tree->insertElement(complexNumber1);
    tree->insertElement(complexNumber2);
    tree->insertElement(complexNumber3);
    {
        auto sumFunction =
                [](const std::complex<long> &a, const std::complex<long> &b) { return a + b; };
        std::complex<long> sum = tree->reduce(std::complex<long>(0, 0), sumFunction);
        assert(sum == std::complex<long>(9, 12));
    }
    {
        auto maxRealFunction =
                [](const std::complex<long> &a, const std::complex<long> &b) { return (a.real() > b.real()) ? a : b; };
        std::complex<long> maxReal = tree->reduce(std::complex<long>(LONG_MIN, 0), maxRealFunction);
        assert(maxReal == std::complex<long>(5, 6));
    }
    delete tree;
    std::cout << "[PASSED] TestReduceComplex" << std::endl;
}

void TestGetBlackHeightLong()
{
    auto *tree = new RedBlackTree<long>(standardLongComparator);
    {
        assert(tree->getBlackHeight() == 1);
    }
    {
        tree->insertElement(10);
        assert(tree->getBlackHeight() == 2);
    }
    {
        tree->insertElement(20);
        tree->insertElement(30);
        assert(tree->getBlackHeight() == 2);
    }
    {
        tree->insertElement(15);
        tree->insertElement(5);
        assert(tree->getBlackHeight() == 3);
    }
    {
        tree->insertElement(25);
        tree->insertElement(35);
        assert(tree->getBlackHeight() == 3);
    }
    delete tree;
    std::cout << "[PASSED] TestGetBlackHeightLong" << std::endl;
}

void TestGetBlackHeightComplex()
{
    auto *tree = new RedBlackTree<std::complex<long>>(standardComplexComparator);
    {
        assert(tree->getBlackHeight() == 1);
    }
    {
        tree->insertElement(std::complex<long>(10, 1));
        assert(tree->getBlackHeight() == 2);
    }
    {
        tree->insertElement(std::complex<long>(20, 2));
        tree->insertElement(std::complex<long>(30, 3));
        assert(tree->getBlackHeight() == 2);
    }
    {
        tree->insertElement(std::complex<long>(15, 4));
        tree->insertElement(std::complex<long>(5, 5));
        assert(tree->getBlackHeight() == 3);
    }
    {
        tree->insertElement(std::complex<long>(25, 6));
        tree->insertElement(std::complex<long>(35, 7));
        assert(tree->getBlackHeight() == 3);
    }
    delete tree;
    std::cout << "[PASSED] TestGetBlackHeightComplex" << std::endl;
}

void TestTreeIteratorLong() {
    auto *tree = new RedBlackTree<long>(standardLongComparator);
    long number1 = 10;
    long number2 = 20;
    long number3 = 30;
    long number4 = 15;
    long number5 = 5;
    tree->insertElement(number1);
    tree->insertElement(number2);
    tree->insertElement(number3);
    tree->insertElement(number4);
    tree->insertElement(number5);
    auto it = tree->begin();
    assert(it->key == number5);
    ++it;
    assert(it->key == number1);
    ++it;
    assert(it->key == number4);
    ++it;
    assert(it->key == number2);
    ++it;
    assert(it->key == number3);
    ++it;
    assert(it == tree->end());
    delete tree;
    std::cout << "[PASSED] TestTreeIteratorLong" << std::endl;
}

void TestTreeIteratorComplex()
{
    auto *tree = new RedBlackTree<std::complex<long>>(standardComplexComparator);
    std::complex<long> complexNumber1(10, 1);
    std::complex<long> complexNumber2(20, 2);
    std::complex<long> complexNumber3(30, 3);
    std::complex<long> complexNumber4(15, 4);
    std::complex<long> complexNumber5(5, 5);
    tree->insertElement(complexNumber1);
    tree->insertElement(complexNumber2);
    tree->insertElement(complexNumber3);
    tree->insertElement(complexNumber4);
    tree->insertElement(complexNumber5);
    auto it = tree->begin();
    assert(it->key == complexNumber5);
    ++it;
    assert(it->key == complexNumber1);
    ++it;
    assert(it->key == complexNumber4);
    ++it;
    assert(it->key == complexNumber2);
    ++it;
    assert(it->key == complexNumber3);
    ++it;
    assert(it == tree->end());
    delete tree;
    std::cout << "[PASSED] TestTreeIteratorComplex" << std::endl;
}

void TestClearLong()
{
    auto *tree = new RedBlackTree<long>(standardLongComparator);
    tree->insertElement(10);
    tree->insertElement(20);
    tree->insertElement(30);
    tree->clear();
    assert(tree->getBlackHeight() == 1);
    assert(tree->begin() == tree->end());
    delete tree;
    std::cout << "[PASSED] TestClearLong" << std::endl;
}

void TestClearComplex()
{
    auto *tree = new RedBlackTree<std::complex<long>>(standardComplexComparator);
    tree->insertElement(std::complex<long>(10, 1));
    tree->insertElement(std::complex<long>(20, 2));
    tree->insertElement(std::complex<long>(30, 3));
    tree->clear();
    assert(tree->getBlackHeight() == 1);
    assert(tree->begin() == tree->end());
    delete tree;
    std::cout << "[PASSED] TestClearComplex" << std::endl;
}

void TestInsertElementPerformance()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long> dis(1, 10000000);
    for (long n = 10000; n <= 10000000; n *= 10)
    {
        auto *tree = new RedBlackTree<long>(standardLongComparator);
        auto start = std::chrono::high_resolution_clock::now();
        for (long i = 0; i < n; ++i)
        {
            tree->insertElement(dis(gen));
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Inserted " << n << " elements in " << duration.count() << " seconds" << std::endl;
        std::cout << "Average time " << duration.count() / static_cast<double>(n) << std::endl;
        delete tree;
    }
}


void AllTestsForRedBlackTree()
{
    TestInsertLong();
    TestInsertComplex();
    TestDeleteLong();
    TestDeleteComplex();
    TestSearchLong();
    TestSearchComplex();
    TestMapLong();
    TestMapComplex();
    TestWhereLong();
    TestWhereComplex();
    TestReduceLong();
    TestReduceComplex();
    TestGetBlackHeightLong();
    TestGetBlackHeightComplex();
    TestTreeIteratorLong();
    TestTreeIteratorComplex();
    TestClearLong();
    TestClearComplex();
    TestInsertElementPerformance();
}
