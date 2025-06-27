#include "avl_tree/avl_tree.h"
#include "dataset/large_reverse.h"
#include "dataset/large_sorted.h"
#include "dataset/large_uniform.h"
#include "dataset/medium_reverse.h"
#include "dataset/medium_sorted.h"
#include "dataset/medium_uniform.h"
#include "dataset/tiny_reverse.h"
#include "dataset/tiny_sorted.h"
#include "dataset/tiny_uniform.h"
#include "container.h"


#include <array>
#include <chrono>
#include <cstring> // for strcmp
#include <iostream>
#include <set>

namespace {
volatile int sink;
template <typename C, typename T, size_t N>
constexpr std::unique_ptr<C> makeSrcContainer(const std::array<T, N> &dataset) {
    std::unique_ptr<C> container = std::make_unique<C>();

    for (auto &datapoint : dataset) {
        container->insert(datapoint);
    }
    return container;
}
//
// template <typename C, typename T, size_t N>
// constexpr C makeDestContainer(const std::array<T, N> &dataset) {
//     C container;
//
//     for (const auto &datapoint : dataset) {
//         container.insert(datapoint);
//     }
//     return container;
// }

template <typename C, typename T, size_t N>
    requires Dontainer<C, T>
double benchmarkRemove(const std::array<T, N> &dataset) {
    auto srcContainer = makeSrcContainer<C>(dataset);
    //C destContainer = makeDestContainer<C>(dataset);

    auto start = std::chrono::high_resolution_clock::now();

    // Remove all elements
    for (auto &datapoint : dataset) {
        bool removed = srcContainer->remove(datapoint);
        if (!removed) {
            sink = sink + 1;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename T, size_t N>
double benchmarkRemoveSet(const std::array<T, N> &dataset) {
    auto srcContainer = makeSrcContainer<std::set<T>>(dataset);
    //std::set<T> destContainer = makeDestContainer<std::set<T>, T, N>(dataset);

    auto start = std::chrono::high_resolution_clock::now();

    // Remove all elements
    for (auto &datapoint : dataset) {
        auto removed = srcContainer->erase(datapoint);

        if (!removed) {
            sink = sink + 1;
        }
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
                duration = benchmarkRemove<AVLTree<int>>(TINY_UNIFORM);
            }

            if (datasetStr == "medium") {
                duration = benchmarkRemove<AVLTree<int>>(MEDIUM_UNIFORM);
            }

            if (datasetStr == "large") {
                duration = benchmarkRemove<AVLTree<int>>(LARGE_UNIFORM);
            }
        } else if (variation == "sorted") {
            if (datasetStr == "tiny") {
                duration = benchmarkRemove<AVLTree<int>>(TINY_SORTED);
            }

            if (datasetStr == "medium") {
                duration = benchmarkRemove<AVLTree<int>>(MEDIUM_SORTED);
            }

            if (datasetStr == "large") {
                duration = benchmarkRemove<AVLTree<int>>(LARGE_SORTED);
            }
        } else {
            if (datasetStr == "tiny") {
                duration = benchmarkRemove<AVLTree<int>>(TINY_REVERSE);
            }

            if (datasetStr == "medium") {
                duration = benchmarkRemove<AVLTree<int>>(MEDIUM_REVERSE);
            }

            if (datasetStr == "large") {
                duration = benchmarkRemove<AVLTree<int>>(LARGE_REVERSE);
            }
        }
    } else {
        if (variation == "random") {
            if (datasetStr == "tiny") {
                duration = benchmarkRemoveSet<>(TINY_UNIFORM);
            }

            if (datasetStr == "medium") {
                duration = benchmarkRemoveSet<>(MEDIUM_UNIFORM);
            }

            if (datasetStr == "large") {
                duration = benchmarkRemoveSet<>(LARGE_UNIFORM);
            }
        } else if (variation == "sorted") {
            if (datasetStr == "tiny") {
                duration = benchmarkRemoveSet<>(TINY_SORTED);
            }

            if (datasetStr == "medium") {
                duration = benchmarkRemoveSet<>(MEDIUM_SORTED);
            }

            if (datasetStr == "large") {
                duration = benchmarkRemoveSet<>(LARGE_SORTED);
            }
        } else {
            if (datasetStr == "tiny") {
                duration = benchmarkRemoveSet<>(TINY_REVERSE);
            }

            if (datasetStr == "medium") {
                duration = benchmarkRemoveSet<>(MEDIUM_REVERSE);
            }

            if (datasetStr == "large") {
                duration = benchmarkRemoveSet<>(LARGE_REVERSE);
            }
        }
    }
    std::cout << duration << "\n";
}
