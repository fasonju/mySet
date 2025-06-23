#include "avl_tree/avl_tree.h"
#include "container.h"
#include "placeholder.h"

#include <array>
#include <chrono>
#include <cstring> // for strcmp
#include <iostream>
#include <set>

namespace {
template <typename C, typename T, size_t N>
    requires Dontainer<C, T>
double testInsert(const std::array<T, N> &dataset) {
    C container;

    auto start = std::chrono::high_resolution_clock::now();

    // Insert all elements
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename T, size_t N>
double testInsertSet(const std::array<T, N> &dataset) {
    std::set<T> container;

    auto start = std::chrono::high_resolution_clock::now();

    // Insert all elements
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}
} // namespace

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <mode>\n";
        std::cerr << "mode: 'avl' or 'set'\n";
        return 1;
    }
    std::string mode = argv[1];

    if (mode == "avl") {
        double duration = testInsert<AVLTree<int>>(placeholder);
        std::cout << duration << "\n";
    } else {
        double duration = testInsertSet(placeholder);
        std::cout << duration << "\n";
    }
}
