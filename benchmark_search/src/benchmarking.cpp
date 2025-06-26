#include "avl_tree/avl_tree.h"
// #include "dataset/large_reverse.h"
// #include "dataset/large_sorted.h"
// #include "dataset/large_uniform.h"
// #include "dataset/medium_reverse.h"
// #include "dataset/medium_sorted.h"
// #include "dataset/medium_uniform.h"
// #include "dataset/tiny_reverse.h"
// #include "dataset/tiny_sorted.h"
// #include "dataset/tiny_uniform.h"
#include "container.h"

#include "placeholder.h"

#include <array>
#include <chrono>
#include <cstring> // for strcmp
#include <iostream>
#include <set>

namespace {
template <typename C, typename T, size_t N>
constexpr std::unique_ptr<C> makeContainer(const std::array<T, N> &dataset) {
    std::unique_ptr<C> container = std::make_unique<C>();

    for (auto &datapoint : dataset) {
        container->insert(datapoint);
    }
    return container;
}

template <typename C, typename T, size_t N>
    requires Dontainer<C, T>
double benchmarkSearch(const std::array<T, N> &dataset) {
    auto srcContainer = makeContainer<C>(dataset);
    C destContainer;

    // Insert all elements
    for (auto &datapoint : *srcContainer) {
        destContainer.insert(datapoint);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Search all elements
    for (auto &datapoint : *srcContainer) {
        volatile bool found = destContainer.contains(datapoint);
        (void)found; // prevent optimization
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename T, size_t N>
double benchmarkSearchSet(const std::array<T, N> &dataset) {
    auto srcContainer = makeContainer<std::set<T>>(dataset);
    std::set<T> destContainer;

    // Insert all elements
    for (auto &datapoint : *srcContainer) {
        destContainer.insert(datapoint);
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Search all elements
    for (auto &datapoint : *srcContainer) {
        volatile bool found = destContainer.find(datapoint) != destContainer.end();
        (void)found;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}
} // namespace

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <mode> <dataset> <variation>\n";
        std::cerr << "mode: 'avl' or 'set'\n";
        std::cerr << "dataset: tiny medium or large";
        std::cerr << "variation: sorted reverse random";

        return 1;
    }
    std::string modeStr = argv[1];
    std::string datasetStr = argv[2];
    std::string variation = argv[3];

    double duration = 0;
    if (modeStr == "avl") {
        if (variation == "random") {
            if (datasetStr == "tiny") {
                duration = benchmarkSearch<AVLTree<int>>(placeholder);
            }

            if (datasetStr == "medium") {
                duration = benchmarkSearch<AVLTree<int>>(placeholder);
            }

            if (datasetStr == "large") {
                duration = benchmarkSearch<AVLTree<int>>(placeholder);
            }
        } else if (variation == "sorted") {
            if (datasetStr == "tiny") {
                duration = benchmarkSearch<AVLTree<int>>(placeholder);
            }

            if (datasetStr == "medium") {
                duration = benchmarkSearch<AVLTree<int>>(placeholder);
            }

            if (datasetStr == "large") {
                duration = benchmarkSearch<AVLTree<int>>(placeholder);
            }
        } else {
            if (datasetStr == "tiny") {
                duration = benchmarkSearch<AVLTree<int>>(placeholder);
            }

            if (datasetStr == "medium") {
                duration = benchmarkSearch<AVLTree<int>>(placeholder);
            }

            if (datasetStr == "large") {
                duration = benchmarkSearch<AVLTree<int>>(placeholder);
            }
        }
    } else {
        if (variation == "random") {
            if (datasetStr == "tiny") {
                duration = benchmarkSearchSet<>(placeholder);
            }

            if (datasetStr == "medium") {
                duration = benchmarkSearchSet<>(placeholder);
            }

            if (datasetStr == "large") {
                duration = benchmarkSearchSet<>(placeholder);
            }
        } else if (variation == "sorted") {
            if (datasetStr == "tiny") {
                duration = benchmarkSearchSet<>(placeholder);
            }

            if (datasetStr == "medium") {
                duration = benchmarkSearchSet<>(placeholder);
            }

            if (datasetStr == "large") {
                duration = benchmarkSearchSet<>(placeholder);
            }
        } else {
            if (datasetStr == "tiny") {
                duration = benchmarkSearchSet<>(placeholder);
            }

            if (datasetStr == "medium") {
                duration = benchmarkSearchSet<>(placeholder);
            }

            if (datasetStr == "large") {
                duration = benchmarkSearchSet<>(placeholder);
            }
        }
    }
    std::cout << duration << "\n";
}
