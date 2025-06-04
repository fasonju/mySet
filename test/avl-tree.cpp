#include "pointer_avl_tree.h"
#include <gtest/gtest.h>
#include <memory>

TEST(Initalization, Initial) {
    auto tree = std::make_unique<PointerAVLTree<int>>();

    EXPECT_TRUE(tree->height() == 0);
    EXPECT_TRUE(tree->empty());
    EXPECT_TRUE(tree->min() == nullptr);
    EXPECT_TRUE(tree->max() == nullptr);
    EXPECT_TRUE(tree->size() == 0);
}

TEST(Insertion, Default) {
    auto tree = std::make_unique<PointerAVLTree<int>>();

    const bool succeeded = tree->insert(1);
    const int *value = tree->search(1);

    EXPECT_TRUE(succeeded);
    EXPECT_TRUE(*value == 1);
}
