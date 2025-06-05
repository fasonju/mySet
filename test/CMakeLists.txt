add_executable(tree_test avl-tree.cpp)
target_link_libraries(tree_test gtest_main tree)
include(GoogleTest)
gtest_discover_tests(tree_test)
