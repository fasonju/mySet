// NOLINTBEGIN
#include "pointer_avl_tree.h"
#include <cstddef>
#include <gtest/gtest.h>
#include <memory>

TEST(AvlTree, Initalization) {
    auto tree = std::make_unique<PointerAVLTree<int>>();

    EXPECT_TRUE(tree->height() == 0);
    EXPECT_TRUE(tree->empty());
    EXPECT_TRUE(tree->min() == nullptr);
    EXPECT_TRUE(tree->max() == nullptr);
    EXPECT_TRUE(tree->size() == 0);
}

TEST(AvlTree, SimpleInsertion) {
    auto tree = std::make_unique<PointerAVLTree<int>>();

    const bool succeeded = tree->insert(1);
    const int *value = tree->search(1);

    EXPECT_TRUE(succeeded);
    EXPECT_TRUE(*value == 1);
}

TEST(AvlTree, DuplicateKeyInsertion) {
    auto tree = std::make_unique<PointerAVLTree<int>>();

    tree->insert(1);
    const bool succeeded = tree->insert(1);
    const int *value = tree->search(1);
    const int height = tree->height();
    const size_t size = tree->size();

    EXPECT_FALSE(succeeded);
    EXPECT_TRUE(*value == 1);
    EXPECT_TRUE(height == 1);
    EXPECT_TRUE(size == 1);
}

TEST(AvlTree, LeftLeftInsertion) {
    auto tree = std::make_unique<PointerAVLTree<int>>();

    tree->insert(4);
    tree->insert(5);
    tree->insert(3);
    tree->insert(2);
    const int preRotationHeight = tree->height();
    const size_t preRotationSize = tree->size();
    tree->insert(1);
    const int postRotationHeight = tree->height();
    const size_t postRotationSize = tree->size();

    EXPECT_TRUE(preRotationHeight == 3);
    EXPECT_TRUE(preRotationSize == 4);
    EXPECT_TRUE(postRotationHeight == 3);
    EXPECT_TRUE(postRotationSize == 5);
}

TEST(AvlTree, RightRightInsertion) {
    auto tree = std::make_unique<PointerAVLTree<int>>();

    tree->insert(2);
    tree->insert(1);
    tree->insert(3);
    tree->insert(4);
    const int preRotationHeight = tree->height();
    const size_t preRotationSize = tree->size();
    tree->insert(5);
    const int postRotationHeight = tree->height();
    const size_t postRotationSize = tree->size();

    EXPECT_TRUE(preRotationHeight == 3);
    EXPECT_TRUE(preRotationSize == 4);
    EXPECT_TRUE(postRotationHeight == 3);
    EXPECT_TRUE(postRotationSize == 5);
}

TEST(AvlTree, LeftRightInsertion) {
    auto tree = std::make_unique<PointerAVLTree<int>>();

    tree->insert(6);
    tree->insert(7);
    tree->insert(5);
    tree->insert(3);
    const int preRotationHeight = tree->height();
    const size_t preRotationSize = tree->size();
    tree->insert(4);
    const int postRotationHeight = tree->height();
    const size_t postRotationSize = tree->size();

    EXPECT_TRUE(preRotationHeight == 3);
    EXPECT_TRUE(preRotationSize == 4);
    EXPECT_TRUE(postRotationHeight == 3);
    EXPECT_TRUE(postRotationSize == 5);
}

TEST(AvlTree, RightLeftInsertion) {
    auto tree = std::make_unique<PointerAVLTree<int>>();

    tree->insert(2);
    tree->insert(1);
    tree->insert(3);
    tree->insert(5);
    const int preRotationHeight = tree->height();
    const size_t preRotationSize = tree->size();
    tree->insert(4);
    const int postRotationHeight = tree->height();
    const size_t postRotationSize = tree->size();

    EXPECT_TRUE(preRotationHeight == 3);
    EXPECT_TRUE(preRotationSize == 4);
    EXPECT_TRUE(postRotationHeight == 3);
    EXPECT_TRUE(postRotationSize == 5);
}
// NOLINTEND
