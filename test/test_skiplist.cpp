// NOLINTBEGIN
#include "skiplist.h"
#include <gtest/gtest.h>
#include <memory>

// TEST(SkipList, Initialization) {
//     auto sl = std::make_unique<SkipList<int>>();
//
//     EXPECT_TRUE(sl->empty());
//     EXPECT_EQ(sl->size(), 0);
//     EXPECT_EQ(sl->min(), nullptr);
//     EXPECT_EQ(sl->max(), nullptr);
// }
//
// TEST(SkipList, SimpleInsertion) {
//     auto sl = std::make_unique<SkipList<int>>();
//
//     const bool succeeded = sl->insert(10);
//     const int* value = sl->search(10);
//
//     EXPECT_TRUE(succeeded);
//     ASSERT_NE(value, nullptr);
//     EXPECT_EQ(*value, 10);
// }
//
// TEST(SkipList, DuplicateInsertion) {
//     auto sl = std::make_unique<SkipList<int>>();
//
//     sl->insert(42);
//     const bool succeeded = sl->insert(42);
//     const int* value = sl->search(42);
//
//     EXPECT_FALSE(succeeded);  // assuming duplicates are not allowed
//     ASSERT_NE(value, nullptr);
//     EXPECT_EQ(*value, 42);
//     EXPECT_EQ(sl->size(), 1);
// }
//
// TEST(SkipList, SearchNotFound) {
//     auto sl = std::make_unique<SkipList<int>>();
//
//     sl->insert(1);
//     const int* value = sl->search(99);
//
//     EXPECT_EQ(value, nullptr);
// }
//
// TEST(SkipList, MinAndMax) {
//     auto sl = std::make_unique<SkipList<int>>();
//
//     sl->insert(30);
//     sl->insert(10);
//     sl->insert(50);
//
//     EXPECT_EQ(*sl->min(), 10);
//     EXPECT_EQ(*sl->max(), 50);
// }
//
// TEST(SkipList, ContainsTest) {
//     auto sl = std::make_unique<SkipList<int>>();
//
//     sl->insert(5);
//     sl->insert(8);
//
//     EXPECT_TRUE(sl->contains(5));
//     EXPECT_TRUE(sl->contains(8));
//     EXPECT_FALSE(sl->contains(100));
// }
//
// TEST(SkipList, RemovalTest) {
//     auto sl = std::make_unique<SkipList<int>>();
//
//     sl->insert(5);
//     sl->insert(10);
//     sl->insert(15);
//
//     const bool removed = sl->remove(10);
//     const int* value = sl->search(10);
//
//     EXPECT_TRUE(removed);
//     EXPECT_EQ(value, nullptr);
//     EXPECT_EQ(sl->size(), 2);
// }
//
// TEST(SkipList, RemoveNonExistent) {
//     auto sl = std::make_unique<SkipList<int>>();
//
//     sl->insert(1);
//     const bool removed = sl->remove(99);
//
//     EXPECT_FALSE(removed);
//     EXPECT_EQ(sl->size(), 1);
// }
//
// TEST(SkipList, ClearTest) {
//     auto sl = std::make_unique<SkipList<int>>();
//
//     sl->insert(3);
//     sl->insert(4);
//     sl->insert(5);
//     sl->clear();
//
//     EXPECT_TRUE(sl->empty());
//     EXPECT_EQ(sl->size(), 0);
//     EXPECT_EQ(sl->search(3), nullptr);
// }
// NOLINTEND
