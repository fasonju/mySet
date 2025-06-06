// NOLINTBEGIN
#include "avl_tree/avl_tree.h"
#include <gtest/gtest.h>

TEST(AvlTree, Initalization) {
    AVLTree<int> tree;

    EXPECT_EQ(tree.height(), 0);
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.min(), nullptr);
    EXPECT_EQ(tree.max(), nullptr);
    EXPECT_EQ(tree.size(), 0u);
}

TEST(AvlTree, SimpleInsertion) {
    AVLTree<int> tree;

    EXPECT_TRUE(tree.insert(1));
    ASSERT_NE(tree.search(1), nullptr);
    EXPECT_EQ(*tree.search(1), 1);
}

TEST(AvlTree, DuplicateKeyInsertion) {
    AVLTree<int> tree;

    tree.insert(1);
    EXPECT_FALSE(tree.insert(1));
    ASSERT_NE(tree.search(1), nullptr);
    EXPECT_EQ(*tree.search(1), 1);
    EXPECT_EQ(tree.height(), 1);
    EXPECT_EQ(tree.size(), 1u);
}

TEST(AvlTree, LeftLeftInsertion) {
    AVLTree<int> tree;

    tree.insert(4);
    tree.insert(5);
    tree.insert(3);
    tree.insert(2);
    EXPECT_EQ(tree.height(), 3);
    EXPECT_EQ(tree.size(), 4u);
    tree.insert(1);
    EXPECT_EQ(tree.height(), 3);
    EXPECT_EQ(tree.size(), 5u);
}

TEST(AvlTree, RightRightInsertion) {
    AVLTree<int> tree;

    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(4);
    EXPECT_EQ(tree.height(), 3);
    EXPECT_EQ(tree.size(), 4u);
    tree.insert(5);
    EXPECT_EQ(tree.height(), 3);
    EXPECT_EQ(tree.size(), 5u);
}

TEST(AvlTree, LeftRightInsertion) {
    AVLTree<int> tree;

    tree.insert(6);
    tree.insert(7);
    tree.insert(5);
    tree.insert(3);
    EXPECT_EQ(tree.height(), 3);
    EXPECT_EQ(tree.size(), 4u);
    tree.insert(4);
    EXPECT_EQ(tree.height(), 3);
    EXPECT_EQ(tree.size(), 5u);
}

TEST(AvlTree, RightLeftInsertion) {
    AVLTree<int> tree;

    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    EXPECT_EQ(tree.height(), 3);
    EXPECT_EQ(tree.size(), 4u);
    tree.insert(4);
    EXPECT_EQ(tree.height(), 3);
    EXPECT_EQ(tree.size(), 5u);
}

TEST(AvlTree, EmptyRemoval) {
    AVLTree<int> tree;
    EXPECT_FALSE(tree.remove(1));
}

TEST(AvlTree, NonExistitantRemoval) {
    AVLTree<int> tree;
    tree.insert(1);
    EXPECT_FALSE(tree.remove(2));
}

TEST(AvlTree, OnlyNodeRemoval) {
    AVLTree<int> tree;
    tree.insert(1);
    EXPECT_TRUE(tree.remove(1));
    EXPECT_EQ(tree.height(), 0);
    EXPECT_EQ(tree.size(), 0u);
}

TEST(AvlTree, RootRemoval) {
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.remove(2);
    EXPECT_EQ(tree.search(2), nullptr);
    EXPECT_TRUE(tree.contains(1));
}

TEST(AvlTree, MiddleRemoval) {
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.remove(3);
    EXPECT_EQ(tree.height(), 2);
    EXPECT_EQ(tree.size(), 3u);
}

TEST(AvlTree, LeafRemoval) {
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.remove(3);
    EXPECT_EQ(tree.size(), 2u);
    EXPECT_EQ(tree.search(3), nullptr);
}

TEST(AvlTree, Clear) {
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.clear();

    EXPECT_EQ(tree.size(), 0);
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.height(), 0);
}

TEST(AVLTree, Search) {
    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    EXPECT_EQ(*tree.search(1), 1);
    EXPECT_EQ(*tree.search(2), 2);
    EXPECT_EQ(*tree.search(3), 3);
    tree.remove(2);
    EXPECT_EQ(tree.search(2), nullptr);
}

TEST(AvlTree, Iteration) {
    AVLTree<int> tree;
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    auto it = tree.begin();
    EXPECT_EQ(*it++, 1);
    EXPECT_EQ(*it++, 2);
    EXPECT_EQ(*it++, 3);
    EXPECT_EQ(it, tree.end());
}

TEST(AvlTree, MinMaxEmptyTree) {
    AVLTree<int> tree;

    EXPECT_EQ(tree.min(), nullptr);
    EXPECT_EQ(tree.max(), nullptr);
}

TEST(AvlTree, MinMaxSingleElement) {
    AVLTree<int> tree;
    tree.insert(42);

    ASSERT_NE(tree.min(), nullptr);
    ASSERT_NE(tree.max(), nullptr);
    EXPECT_EQ(*tree.min(), 42);
    EXPECT_EQ(*tree.max(), 42);
}

TEST(AvlTree, MinMaxMultipleElements) {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);

    ASSERT_NE(tree.min(), nullptr);
    ASSERT_NE(tree.max(), nullptr);
    EXPECT_EQ(*tree.min(), 5);
    EXPECT_EQ(*tree.max(), 20);
}

TEST(AvlTree, ContainsFunctionality) {
    AVLTree<int> tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(9);

    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(9));
    EXPECT_FALSE(tree.contains(4));
    EXPECT_FALSE(tree.contains(10));
}

TEST(AvlTree, SizeAndEmpty) {
    AVLTree<int> tree;

    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0u);

    tree.insert(1);
    EXPECT_FALSE(tree.empty());
    EXPECT_EQ(tree.size(), 1u);

    tree.insert(2);
    tree.insert(3);
    EXPECT_EQ(tree.size(), 3u);

    tree.remove(2);
    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_EQ(tree.size(), 2u);
}

TEST(AvlTree, HeightTracking) {
    AVLTree<int> tree;

    EXPECT_EQ(tree.height(), 0);

    tree.insert(1);
    EXPECT_EQ(tree.height(), 1);

    tree.insert(2);
    tree.insert(3); // Causes balancing
    EXPECT_EQ(tree.height(), 2);

    tree.insert(4);
    tree.insert(5);
    EXPECT_EQ(tree.height(), 3);
}

// NOLINTEND
