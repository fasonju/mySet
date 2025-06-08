#include "avl_tree/avl_tree.h"
#include "container.h"
#include "placeholder.h"
#include <array>
#include <iostream>
#include <set>

namespace {
template <typename C, typename T, size_t N>
    requires Dontainer<C, T>
void testInserts(const std::array<T, N> &dataset) {
    C container;
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    for (auto &datapoint : dataset) {
        container.remove(datapoint);
    }

    std::cout << container.size() << "\n";
}

template <typename T, size_t N>
void testInsertsSet(const std::array<T, N> &dataset) {
    std::set<T> set;
    for (auto &datapoint : dataset) {
        set.insert(datapoint);
    }

    for (auto &datapoint : dataset) {
        set.erase(datapoint);
    }

    std::cout << set.size() << "\n";
}

} // namespace

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::exit(1);
    }
    std::string arg = argv[1];
    if (arg == "avl") {
        std::cout << "AVL" << "\n";
        testInserts<AVLTree<int>>(placeholder);
    } else {
        std::cout << "Set" << "\n";
        testInsertsSet(placeholder);
    }
}
