#include "avl_tree/avl_tree.h"
#include "container.h"
#include "large_uniform.h"
#include "log.h"
#include <array>
#include <iostream>
#include <set>

namespace {
template <typename C, typename T, size_t N>
    requires Dontainer<C, T>
void testInserts(const std::array<T, N> &dataset) {
    C container;
    std::set<T> set;
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
        // set.insert(datapoint);
    }

    std::cout << container.size() << "\n";
}
} // namespace

int main() { testInserts<AVLTree<int>>(large_uniform); }
