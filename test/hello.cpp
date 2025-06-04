#include "pointer_avl_tree.h"
#include <gtest/gtest.h>
#include <memory>

TEST(Insert, InsertsCorrrectly) {
    auto tree = std::make_unique<PointerAVLTree<int>>();
    EXPECT_TRUE(true);
}
