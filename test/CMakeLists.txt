add_executable(avl_test avl_tree.cpp)
add_executable(skiplist_test skiplist.cpp)

target_link_libraries(avl_test gtest_main container)
target_link_libraries(skiplist_test gtest_main container)
include(GoogleTest)
gtest_discover_tests(avl_test)
gtest_discover_tests(skiplist_test)

