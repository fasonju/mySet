// // NOLINTBEGIN
// #include "skiplist/skiplist.h"
// #include <gtest/gtest.h>
//
// TEST(SkipList, Initialization) {
//     SkipList<int> list;
//
//     EXPECT_TRUE(list.empty());
//     EXPECT_EQ(list.size(), 0u);
//     EXPECT_EQ(list.min(), nullptr);
//     EXPECT_EQ(list.max(), nullptr);
// }
//
// TEST(SkipList, SimpleInsertion) {
//     SkipList<int> list;
//
//     EXPECT_TRUE(list.insert(1));
//     ASSERT_NE(list.search(1), nullptr);
//     EXPECT_EQ(*list.search(1), 1);
// }
//
// TEST(SkipList, DuplicateKeyInsertion) {
//     SkipList<int> list;
//
//     list.insert(1);
//     EXPECT_FALSE(list.insert(1));
//     ASSERT_NE(list.search(1), nullptr);
//     EXPECT_EQ(*list.search(1), 1);
//     EXPECT_EQ(list.size(), 1u);
// }
//
// TEST(SkipList, EmptyRemoval) {
//     SkipList<int> list;
//     EXPECT_FALSE(list.remove(1));
// }
//
// TEST(SkipList, NonExistentRemoval) {
//     SkipList<int> list;
//     list.insert(1);
//     EXPECT_FALSE(list.remove(2));
// }
//
// TEST(SkipList, OnlyNodeRemoval) {
//     SkipList<int> list;
//     list.insert(1);
//     EXPECT_TRUE(list.remove(1));
//     EXPECT_EQ(list.size(), 0u);
//     EXPECT_TRUE(list.empty());
// }
//
// TEST(SkipList, Clear) {
//     SkipList<int> list;
//     list.insert(1);
//     list.insert(2);
//     list.clear();
//
//     EXPECT_EQ(list.size(), 0);
//     EXPECT_TRUE(list.empty());
// }
//
// TEST(SkipList, Search) {
//     SkipList<int> list;
//     list.insert(1);
//     list.insert(2);
//     list.insert(3);
//
//     EXPECT_EQ(*list.search(1), 1);
//     EXPECT_EQ(*list.search(2), 2);
//     EXPECT_EQ(*list.search(3), 3);
//     list.remove(2);
//     EXPECT_EQ(list.search(2), nullptr);
// }
//
// // TEST(SkipList, Iteration) {
// //     SkipList<int> list;
// //     list.insert(3);
// //     list.insert(2);
// //     list.insert(1);
// //
// //     auto it = list.begin();
// //     EXPECT_EQ(*it++, 1);
// //     EXPECT_EQ(*it++, 2);
// //     EXPECT_EQ(*it++, 3);
// //     EXPECT_EQ(it, list.end());
// // }
//
// TEST(SkipList, MinMaxEmptyList) {
//     SkipList<int> list;
//
//     EXPECT_EQ(list.min(), nullptr);
//     EXPECT_EQ(list.max(), nullptr);
// }
//
// TEST(SkipList, MinMaxSingleElement) {
//     SkipList<int> list;
//     list.insert(42);
//
//     ASSERT_NE(list.min(), nullptr);
//     ASSERT_NE(list.max(), nullptr);
//     EXPECT_EQ(*list.min(), 42);
//     EXPECT_EQ(*list.max(), 42);
// }
//
// TEST(SkipList, MinMaxMultipleElements) {
//     SkipList<int> list;
//     list.insert(10);
//     list.insert(20);
//     list.insert(5);
//     list.insert(15);
//
//     ASSERT_NE(list.min(), nullptr);
//     ASSERT_NE(list.max(), nullptr);
//     EXPECT_EQ(*list.min(), 5);
//     EXPECT_EQ(*list.max(), 20);
// }
//
// TEST(SkipList, ContainsFunctionality) {
//     SkipList<int> list;
//     list.insert(7);
//     list.insert(3);
//     list.insert(9);
//
//     EXPECT_TRUE(list.contains(3));
//     EXPECT_TRUE(list.contains(7));
//     EXPECT_TRUE(list.contains(9));
//     EXPECT_FALSE(list.contains(4));
//     EXPECT_FALSE(list.contains(10));
// }
//
// TEST(SkipList, SizeAndEmpty) {
//     SkipList<int> list;
//
//     EXPECT_TRUE(list.empty());
//     EXPECT_EQ(list.size(), 0u);
//
//     list.insert(1);
//     EXPECT_FALSE(list.empty());
//     EXPECT_EQ(list.size(), 1u);
//
//     list.insert(2);
//     list.insert(3);
//     EXPECT_EQ(list.size(), 3u);
//
//     list.remove(2);
//     EXPECT_TRUE(list.contains(1));
//     EXPECT_TRUE(list.contains(3));
//     EXPECT_EQ(list.size(), 2u);
// }
//
// // NOLINTEND
