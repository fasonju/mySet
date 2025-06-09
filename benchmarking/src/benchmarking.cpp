#include "avl_tree/avl_tree.h"
#include "container.h"
#include "dataset/medium_reverse.h" // renamed from large_reversed
#include "dataset/medium_sorted.h"
#include "dataset/medium_uniform.h"

#include <array>
#include <chrono>
#include <iostream>
#include <set>

namespace {
template <typename C, typename T, size_t N>
    requires Dontainer<C, T>
double testInsertSearchRemove(const std::array<T, N> &dataset) {
    C container;

    auto start = std::chrono::high_resolution_clock::now();

    // Insert all elements
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    // Search all elements
    for (auto &datapoint : dataset) {
        volatile bool found = container.contains(datapoint);
        (void)found; // prevent optimization
    }

    // Remove all elements
    for (auto &datapoint : dataset) {
        container.remove(datapoint);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename T, size_t N>
double testInsertSearchRemoveSet(const std::array<T, N> &dataset) {
    std::set<T> container;

    auto start = std::chrono::high_resolution_clock::now();

    // Insert all elements
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    // Search all elements
    for (auto &datapoint : dataset) {
        volatile bool found = container.find(datapoint) != container.end();
        (void)found;
    }

    // Remove all elements
    for (auto &datapoint : dataset) {
        container.erase(datapoint);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename T, size_t N>
void runFullTest(const std::array<T, N> &dataset,
                 const std::string &datasetName) {
    std::cout << "Dataset: " << datasetName << "\n";

    double avlTime = testInsertSearchRemove<AVLTree<T>>(dataset);
    std::cout << "AVLTree insert+search+remove time: " << avlTime << " ms\n";

    double setTime = testInsertSearchRemoveSet(dataset);
    std::cout << "std::set insert+search+erase time: " << setTime << " ms\n";

    double percentDiff = 100.0 * (avlTime - setTime) / setTime;
    std::cout << "Difference (AVL vs std::set): " << percentDiff << "%\n\n";
}

template <typename C, typename T, size_t N>
    requires Dontainer<C, T>
double testInsertHeavySearchLight(const std::array<T, N> &dataset,
                                  size_t searchRepeats) {
    C container;

    // Insert once
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Perform many searches
    for (size_t repeat = 0; repeat < searchRepeats; ++repeat) {
        for (auto &datapoint : dataset) {
            volatile bool found = container.contains(datapoint);
            (void)found;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename T, size_t N>
double testInsertHeavySearchLightSet(const std::array<T, N> &dataset,
                                     size_t searchRepeats) {
    std::set<T> container;

    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t repeat = 0; repeat < searchRepeats; ++repeat) {
        for (auto &datapoint : dataset) {
            volatile bool found = container.find(datapoint) != container.end();
            (void)found;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename T, size_t N>
void runAVLStrongSearchTest(const std::array<T, N> &dataset,
                            size_t searchRepeats,
                            const std::string &datasetName) {
    std::cout << "Dataset: " << datasetName << " (search repeated "
              << searchRepeats << "x)\n";

    double avlTime =
        testInsertHeavySearchLight<AVLTree<T>>(dataset, searchRepeats);
    std::cout << "AVLTree insert + repeated search time: " << avlTime
              << " ms\n";

    double setTime = testInsertHeavySearchLightSet(dataset, searchRepeats);
    std::cout << "std::set insert + repeated search time: " << setTime
              << " ms\n";

    double percentDiff = 100.0 * (avlTime - setTime) / setTime;
    std::cout << "Difference (AVL vs std::set): " << percentDiff << "%\n\n";
}

} // namespace

int main() {
    runFullTest(MEDIUM_UNIFORM, "Uniform Random");
    runFullTest(MEDIUM_SORTED, "Sorted");
    runFullTest(MEDIUM_REVERSE, "Reverse");

    constexpr size_t searchRepeats = 100;
    runAVLStrongSearchTest(MEDIUM_UNIFORM, searchRepeats, "Uniform Random");
    runAVLStrongSearchTest(MEDIUM_SORTED, searchRepeats, "Sorted");
    runAVLStrongSearchTest(MEDIUM_REVERSE, searchRepeats, "Reverse");

    return 0;
}
