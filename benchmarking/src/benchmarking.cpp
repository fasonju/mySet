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
    if (argc < 2) {
        std::cerr << "Missing argument\n";
        return 1;
    }

    std::vector<std::string> args(argv, argv + argc);
    const std::string &arg = args.at(1); // Safe and clang-tidy compliant

    if (arg == "avl") {
        std::cout << "AVL\n";
        testInserts<AVLTree<int>>(placeholder);
    } else {
        std::cout << "Set\n";
        testInsertsSet(placeholder);
    }
}
