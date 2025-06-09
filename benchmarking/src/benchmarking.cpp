#include "avl_tree/avl_tree.h"
#include "container.h"
#include "dataset/large_uniform.h"
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
}

} // namespace

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Missing argument\n";
        return 1;
    }

    std::vector<std::string> args(argv, argv + argc);
    const std::string &arg = args.at(1); // Safe and clang-tidy compliant

    auto start = std::chrono::high_resolution_clock::now();
    if (arg == "avl") {
        std::cout << "AVL\n";
        testInserts<AVLTree<int>>(LARGE_UNIFORM);
    } else {
        std::cout << "Set\n";
        testInsertsSet(LARGE_UNIFORM);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;

    std::cout << "Time taken: " << duration_ms.count() << " ms" << std::endl;
    return 0;
}
