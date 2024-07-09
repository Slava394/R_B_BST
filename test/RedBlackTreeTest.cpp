// #include <iostream>
// #include <cassert>
// #include <complex>
// #include <functional>
// #include <vector>
// #include "../src/RedBlackTree.h"
// #include "RedBlackTreeTest.h"
//
//
// int standardLongComparator(const long& a, const long& b)
// {
//     if (a < b) return 1;
//     if (a > b) return -1;
//     return 0;
// }
//
// void TestInsertLong()
// {
//     auto *tree = new RedBlackTree<long>(standardLongComparator);
//     {
//         tree->insertElement(10);
//         tree->insertElement(10);
//         assert(tree->searchElement(10) != nullptr);
//     }
//     {
//         for (long index{1}; index <= 5; ++index)
//         {
//             tree->insertElement(index);
//         }
//         for (long index{1}; index <= 5; ++index)
//         {
//             assert(tree->searchElement(index) != nullptr);
//         }
//     }
//     {
//         for (long index{10}; index >= 6; --index)
//         {
//             tree->insertElement(index);
//         }
//         for (long index{6}; index <= 10; ++index)
//         {
//             assert(tree->searchElement(index) != nullptr);
//         }
//     }
//     {
//         tree->insertElement(11);
//         tree->insertElement(12);
//         tree->insertElement(15);
//         tree->deleteElement(12);
//         tree->deleteElement(15);
//         assert(tree->searchElement(12) == nullptr);
//         assert(tree->searchElement(15) == nullptr);
//         assert(tree->searchElement(11) != nullptr);
//     }
//     {
//         tree->insertElement(10);
//         assert(tree->searchElement(10) != nullptr);
//     }
//     delete tree;
//     std::cout << "[PASSED] testInsertLong" << std::endl;
// }
//
// void TestDeleteLong()
// {
//     RedBlackTree<long> tree([](const long& a, const long& b)
//     {
//         if (a < b) return -1;
//         if (a > b) return 1;
//         return 0;
//     });
//     {
//         tree.insertElement(10);
//         tree.deleteElement(10);
//         tree.deleteElement(10);
//         assert(tree.searchElement(10) == nullptr);
//     }
//     {
//         tree.insertElement(10);
//         tree.deleteElement(20);
//         assert(tree.searchElement(10) != nullptr);
//     }
//     {
//         for (long index{1}; index <= 5; ++index)
//         {
//             tree.insertElement(index);
//         }
//         for (long index{1}; index <= 5; ++index)
//         {
//             tree.deleteElement(index);
//         }
//         for (long index{1}; index <= 5; ++index)
//         {
//             assert(tree.searchElement(index) == nullptr);
//         }
//     }
//     {
//         for (long index{5}; index >= 1; --index)
//         {
//             tree.insertElement(index);
//         }
//         for (long index{5}; index >= 1; --index)
//         {
//             tree.deleteElement(index);
//         }
//         for (long index{1}; index <= 5; ++index)
//         {
//             assert(tree.searchElement(index) == nullptr);
//         }
//     }
//     std::cout << "[PASSED] testDeleteLong" << std::endl;
// }
//
// void TestInsertComplex()
// {
//     RedBlackTree<std::complex<long>> tree([](const std::complex<long>& a, const std::complex<long>& b)
//     {
//         if (a.real() < b.real()) return -1;
//         if (a.real() > b.real()) return 1;
//         if (a.imag() < b.imag()) return -1;
//         if (a.imag() > b.imag()) return 1;
//         return 0;
//     });
//     {
//         std::complex<long> c1(2, 3);
//         tree.insertElement(c1);
//         assert(tree.searchElement(c1) != nullptr);
//     }
//     {
//         for (long index{1}; index <= 5; ++index)
//         {
//             std::complex c(index, index * 2);
//             tree.insertElement(c);
//             assert(tree.searchElement(c) != nullptr);
//         }
//     }
//     {
//         std::complex<long> c2(1, 2);
//         std::complex<long> c3(3, 4);
//         std::complex<long> c4(-1, -2);
//         tree.insertElement(c2);
//         tree.insertElement(c3);
//         tree.insertElement(c4);
//         assert(tree.searchElement(c2) != nullptr);
//         assert(tree.searchElement(c3) != nullptr);
//         assert(tree.searchElement(c4) != nullptr);
//         tree.deleteElement(c2);
//         tree.deleteElement(c4);
//         assert(tree.searchElement(c2) == nullptr);
//         assert(tree.searchElement(c4) == nullptr);
//         assert(tree.searchElement(c3) != nullptr);
//     }
//     {
//         std::complex<long> c5(10, 20);
//         tree.insertElement(c5);
//         assert(tree.searchElement(c5) != nullptr);
//         std::complex<long> c6(5, 5);
//         tree.insertElement(c6);
//         assert(tree.searchElement(c6) != nullptr);
//     }
//     std::cout << "[PASSED] testInsertComplex" << std::endl;
// }
//
// void TestDeleteComplex()
// {
//     RedBlackTree<std::complex<long>> tree([](const std::complex<long>& a, const std::complex<long>& b)
//     {
//         if (a.real() < b.real()) return -1;
//         if (a.real() > b.real()) return 1;
//         if (a.imag() < b.imag()) return -1;
//         if (a.imag() > b.imag()) return 1;
//         return 0;
//     });
//     {
//         std::complex<long> c1(2, 3);
//         tree.insertElement(c1);
//         tree.deleteElement(c1);
//         assert(tree.searchElement(c1) == nullptr);
//     }
//     {
//         for (long index{1}; index <= 5; ++index)
//         {
//             std::complex c( index, index * 2);
//             tree.insertElement(c);
//         }
//         for (long index{1}; index <= 5; ++index)
//         {
//             std::complex c(index, index * 2);
//             tree.deleteElement(c);
//             assert(tree.searchElement(c) == nullptr);
//         }
//     }
//     {
//         std::complex<long> c2(1, 2);
//         tree.insertElement(c2);
//         tree.deleteElement(c2);
//         assert(tree.searchElement(c2) == nullptr);
//     }
//     std::cout << "[PASSED] testDeleteComplex" << std::endl;
// }
//
// void TestSearchElementComplexLong()
// {
//     RedBlackTree<std::complex<long>> tree([](const std::complex<long>& a, const std::complex<long>& b)
//     {
//         if (a.real() < b.real()) return -1;
//         if (a.real() > b.real()) return 1;
//         if (a.imag() < b.imag()) return -1;
//         if (a.imag() > b.imag()) return 1;
//         return 0;
//     });
//     {
//         tree.insertElement(std::complex<long>(5, 2));
//         tree.insertElement(std::complex<long>(7, 3));
//         tree.insertElement(std::complex<long>(3, 1));
//         tree.insertElement(std::complex<long>(1, 4));
//     }
//     {
//         assert(tree.searchElement(std::complex<long>(5, 2)) != nullptr);
//         assert(tree.searchElement(std::complex<long>(7, 3)) != nullptr);
//         assert(tree.searchElement(std::complex<long>(3, 1)) != nullptr);
//         assert(tree.searchElement(std::complex<long>(1, 4)) != nullptr);
//     }
//     {
//         assert(tree.searchElement(std::complex<long>(2, 1)) == nullptr);
//         assert(tree.searchElement(std::complex<long>(6, 5)) == nullptr);
//         assert(tree.searchElement(std::complex<long>(4, 3)) == nullptr);
//         assert(tree.searchElement(std::complex<long>(8, 2)) == nullptr);
//     }
//     std::cout << "[PASSED] testSearchElementComplexLong" << std::endl;
// }
//
// void TestSearchElementLong()
// {
//     RedBlackTree<long> tree([](const long& a, const long& b)
//     {
//         if (a < b) return -1;
//         if (a > b) return 1;
//         return 0;
//     });
//     {
//         tree.insertElement(5);
//         tree.insertElement(7);
//         tree.insertElement(3);
//         tree.insertElement(1);
//     }
//     {
//         assert(tree.searchElement(5) != nullptr);
//         assert(tree.searchElement(7) != nullptr);
//         assert(tree.searchElement(3) != nullptr);
//         assert(tree.searchElement(1) != nullptr);
//     }
//     {
//         assert(tree.searchElement(2) == nullptr);
//         assert(tree.searchElement(6) == nullptr);
//         assert(tree.searchElement(4) == nullptr);
//         assert(tree.searchElement(8) == nullptr);
//     }
//     std::cout << "[PASSED] testSearchElementLong" << std::endl;
// }
//
// void TestSearchSubtreeLong()
// {
//     RedBlackTree<long> tree([](const long& a, const long& b)
//     {
//         if (a < b) return -1;
//         if (a > b) return 1;
//         return 0;
//     });
//     {
//         tree.insertElement(5);
//         tree.insertElement(3);
//         tree.insertElement(7);
//         tree.insertElement(2);
//         tree.insertElement(4);
//         tree.insertElement(6);
//         tree.insertElement(8);
//     }
//     {
//         // assert(tree.searchSubtree(3));
//         // assert(tree.searchSubtree(7));
//         // assert(tree.searchSubtree(2));
//         // assert(tree.searchSubtree(4));
//         // assert(tree.searchSubtree(6));
//         // assert(tree.searchSubtree(8));
//     }
//     std::cout << "[PASSED] testSearchSubtreeLong" << std::endl;
// }
//
// void TestIteratorLong()
// {
//     RedBlackTree<long> tree([](const long& a, const long& b)
//     {
//         if (a < b) return 1;
//         if (a > b) return -1;
//         return 0;
//     });
//     tree.insertElement(5);
//     tree.insertElement(3);
//     tree.insertElement(7);
//     tree.insertElement(2);
//     tree.insertElement(4);
//     tree.insertElement(6);
//     tree.insertElement(8);
//     std::vector<long> expectedOrder = {2, 3, 4, 5, 6, 7, 8};
//     auto it = expectedOrder.begin();
//     // auto &treeStart = *tree.begin();
//     // auto &treeEnd = *tree.end();
//     // while (treeStart != treeEnd) {
//     //     assert(treeStart->key == *it);
//     //     ++treeStart;
//     //     ++it;
//     // }
//     // delete &treeStart;
//     // delete &treeEnd;
//     std::cout << "[PASSED] testIteratorLong" << std::endl;
// }
//
// void TestIteratorComplex()
// {
//     RedBlackTree<std::complex<long>> tree([](const std::complex<long>& a, const std::complex<long>& b)
//     {
//         if (a.real() < b.real()) return 1;
//         if (a.real() > b.real()) return -1;
//         if (a.imag() < b.imag()) return 1;
//         if (a.imag() > b.imag()) return -1;
//         return 0;
//     });
//     tree.insertElement(std::complex<long>(5, 2));
//     tree.insertElement(std::complex<long>(3, 4));
//     tree.insertElement(std::complex<long>(7, 1));
//     tree.insertElement(std::complex<long>(2, 5));
//     tree.insertElement(std::complex<long>(4, 3));
//     tree.insertElement(std::complex<long>(6, 0));
//     tree.insertElement(std::complex<long>(8, 6));
//     std::vector expectedOrder =
//     {
//         std::complex<long>(2, 5),
//         std::complex<long>(3, 4),
//         std::complex<long>(4, 3),
//         std::complex<long>(5, 2),
//         std::complex<long>(6, 0),
//         std::complex<long>(7, 1),
//         std::complex<long>(8, 6)
//     };
//     auto it = expectedOrder.begin();
//     // auto &treeStart = *tree.begin();
//     // auto &treeEnd = *tree.end();
//     // while (treeStart != treeEnd) {
//     //     assert(treeStart->key.imag() == it->imag() && treeStart->key.real() == it->real());
//     //     ++treeStart;
//     //     ++it;
//     // }
//     // delete &treeStart;
//     // delete &treeEnd;
//     std::cout << "[PASSED] testIteratorComplex" << std::endl;
// }
//
// void mapTripleLong(TreeNode *node)
// {
//     node->key *= 3;
// }
//
// void mapDoubleLong(TreeNode<long> *node)
// {
//     node->key *= 2;
// }
//
// void mapSquareLong(TreeNode<long> *node)
// {
//     node->key = node->key * node->key;
// }
//
// void mapNegateLong(TreeNode<long> *node)
// {
//     node->key = node->key - 5;
// }
//
// void TestMapLong()
// {
//     {
//         RedBlackTree<long> tree([](const long& a, const long& b)
//         {
//             if (a < b) return 1;
//             if (a > b) return -1;
//             return 0;
//         });
//         tree.insertElement(5);
//         tree.insertElement(3);
//         tree.insertElement(7);
//         tree.insertElement(2);
//         tree.insertElement(4);
//         tree.map(mapTripleLong);
//         assert(tree.searchElement(6) != nullptr);
//         assert(tree.searchElement(6)->key == 6);
//         assert(tree.searchElement(9) != nullptr);
//         assert(tree.searchElement(9)->key == 9);
//         assert(tree.searchElement(15) != nullptr);
//         assert(tree.searchElement(15)->key == 15);
//         assert(tree.searchElement(21) != nullptr);
//         assert(tree.searchElement(21)->key == 21);
//         assert(tree.searchElement(12) != nullptr);
//         assert(tree.searchElement(12)->key == 12);
//     }
//     {
//         RedBlackTree<long> tree([](const long& a, const long& b)
//         {
//             if (a < b) return 1;
//             if (a > b) return -1;
//             return 0;
//         });
//         tree.insertElement(5);
//         tree.insertElement(3);
//         tree.insertElement(7);
//         tree.insertElement(2);
//         tree.insertElement(4);
//         tree.map(mapDoubleLong);
//         assert(tree.searchElement(4) != nullptr);
//         assert(tree.searchElement(4)->key == 4);
//         assert(tree.searchElement(8) != nullptr);
//         assert(tree.searchElement(8)->key == 8);
//         assert(tree.searchElement(14) != nullptr);
//         assert(tree.searchElement(14)->key == 14);
//         assert(tree.searchElement(6) != nullptr);
//         assert(tree.searchElement(6)->key == 6);
//         assert(tree.searchElement(10) != nullptr);
//         assert(tree.searchElement(10)->key == 10);
//         tree.map(mapSquareLong);
//         assert(tree.searchElement(64) != nullptr);
//         assert(tree.searchElement(64)->key == 64);
//         assert(tree.searchElement(196) != nullptr);
//         assert(tree.searchElement(196)->key == 196);
//         assert(tree.searchElement(36) != nullptr);
//         assert(tree.searchElement(36)->key == 36);
//         assert(tree.searchElement(100) != nullptr);
//         assert(tree.searchElement(100)->key == 100);
//         assert(tree.searchElement(16) != nullptr);
//         assert(tree.searchElement(16)->key == 16);
//         tree.map(mapNegateLong);
//         assert(tree.searchElement(59) != nullptr);
//         assert(tree.searchElement(59)->key == 59);
//         assert(tree.searchElement(191) != nullptr);
//         assert(tree.searchElement(191)->key == 191);
//         assert(tree.searchElement(31) != nullptr);
//         assert(tree.searchElement(31)->key == 31);
//         assert(tree.searchElement(95) != nullptr);
//         assert(tree.searchElement(95)->key == 95);
//         assert(tree.searchElement(11) != nullptr);
//         assert(tree.searchElement(11)->key == 11);
//     }
//     std::cout << "[PASSED] testMapLong" << std::endl;
// }
//
// void mapTripleComplexLong(TreeNode<std::complex<long>> *node) {
//     node->key *= 3;
// }
//
// void mapDoubleComplexLong(TreeNode<std::complex<long>> *node) {
//     node->key *= 2;
// }
//
// void mapSquareComplexLong(TreeNode<std::complex<long>> *node) {
//     node->key = std::pow(node->key, 2);
// }
//
// void mapNegateComplexLong(TreeNode<std::complex<long>> *node) {
//     node->key = node->key.real() - 5;
// }
//
// void AllTestsForRedBlackTree()
// {
//     TestInsertLong();
//     TestInsertComplex();
//     TestSearchElementLong();
//     TestSearchElementComplexLong();
//     TestDeleteLong();
//     TestDeleteComplex();
//     TestSearchSubtreeLong();
//     TestIteratorLong();
//     TestIteratorComplex();
//     TestMapLong();
// }
