#include "avl_tree/avl_tree.h"
#include "container.h"
#include "placeholder.h"

#include <array>
#include <chrono>
#include <cstring> // for strcmp
#include <iostream>
#include <set>
#include <string>

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

template <typename C, typename T, size_t N>
    requires Dontainer<C, T>
double testSearch(const std::array<T, N> &dataset) {
    C container;

    // Insert elements before timer
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Search all elements
    for (auto &datapoint : dataset) {
        volatile bool found = container.contains(datapoint);
        (void)found; // prevent optimization
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename C, typename T, size_t N>
    requires Dontainer<C, T>
double testRemove(const std::array<T, N> &dataset) {
    C container;

    // Insert elements before timer
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Remove all elements
    for (auto &datapoint : dataset) {
        container.remove(datapoint);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

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

template <typename T, size_t N>
double testSearchSet(const std::array<T, N> &dataset) {
    std::set<T> container;

    // Insert elements before timer
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Search all elements
    for (auto &datapoint : dataset) {
        volatile bool found = container.find(datapoint) != container.end();
        (void)found;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename T, size_t N>
double testRemoveSet(const std::array<T, N> &dataset) {
    std::set<T> container;

    // Insert elements before timer
    for (auto &datapoint : dataset) {
        container.insert(datapoint);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Remove all elements
    for (auto &datapoint : dataset) {
        container.erase(datapoint);
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
void runFullTestMode(const std::array<T, N> &dataset,
                     const std::string &datasetName, const std::string &mode) {
    std::cout << "Dataset: " << datasetName << "\n";

    if (mode == "avl") {
        double avlInsertTime = testInsert<AVLTree<T>>(dataset);
        std::cout << "AVLTree insert time: " << avlInsertTime
                  << " ms\n";
        double avlSearchTime = testSearch<AVLTree<T>>(dataset);
        std::cout << "AVLTree search time: " << avlSearchTime
                  << " ms\n";
        double avlEraseTime = testRemove<AVLTree<T>>(dataset);
        std::cout << "AVLTree remove time: " << avlEraseTime
                  << " ms\n";
        double avlTime = testInsertSearchRemove<AVLTree<T>>(dataset);
        std::cout << "AVLTree insert+search+remove time: " << avlTime
                  << " ms\n";
    } else if (mode == "set") {
        double setInsertTime = testInsertSet(dataset);
        std::cout << "std::set insert time: " << setInsertTime
                  << " ms\n";
        double setSearchTime = testSearchSet(dataset);
        std::cout << "std::set search time: " << setSearchTime
                  << " ms\n";
        double setEraseTime = testRemoveSet(dataset);
        std::cout << "std::set erase time: " << setEraseTime
                  << " ms\n";
        double setTime = testInsertSearchRemoveSet(dataset);
        std::cout << "std::set insert+search+erase time: " << setTime
                  << " ms\n";
    } else {
        std::cerr << "Unknown mode '" << mode << "'. Use 'avl' or 'set'.\n";
    }

    std::cout << "\n";
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
void runStrongSearchTestMode(const std::array<T, N> &dataset,
                             size_t searchRepeats,
                             const std::string &datasetName,
                             const std::string &mode) {
    std::cout << "Dataset: " << datasetName << " (search repeated "
              << searchRepeats << "x)\n";

    if (mode == "avl") {
        double avlTime =
            testInsertHeavySearchLight<AVLTree<T>>(dataset, searchRepeats);
        std::cout << "AVLTree insert + repeated search time: " << avlTime
                  << " ms\n";
    } else if (mode == "set") {
        double setTime = testInsertHeavySearchLightSet(dataset, searchRepeats);
        std::cout << "std::set insert + repeated search time: " << setTime
                  << " ms\n";
    } else {
        std::cerr << "Unknown mode '" << mode << "'. Use 'avl' or 'set'.\n";
    }

    std::cout << "\n";
}

} // namespace

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <mode>\n";
        std::cerr << "mode: 'avl' or 'set'\n";
        return 1;
    }

    std::string mode = argv[1];

    runFullTestMode(placeholder, "Uniform Random", mode);
    runFullTestMode(placeholder, "Sorted", mode);
    runFullTestMode(placeholder, "Reverse", mode);

    constexpr size_t searchRepeats = 100;
    runStrongSearchTestMode(placeholder, searchRepeats, "Uniform Random",
                            mode);
    runStrongSearchTestMode(placeholder, searchRepeats, "Sorted", mode);
    runStrongSearchTestMode(placeholder, searchRepeats, "Reverse", mode);

    return 0;
}
