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

#include <chrono>
#include <iostream>
#include <memory>
#include <set>

namespace {
volatile int sink;
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
double benchmarkIteration(const std::array<T, N> &dataset) {
    auto container = makeContainer<C>(dataset);
    // const int random = std::rand();
    auto start = std::chrono::high_resolution_clock::now();

    for (auto &datapoint : *container) {
        sink = sink + 1;
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;
    return duration_ms.count();
}

template <typename T, size_t N>
double benchmarkIterationSet(const std::array<T, N> &dataset) {
    auto container = makeContainer<std::set<T>>(dataset);

    auto start = std::chrono::high_resolution_clock::now();

    for (auto &datapoint : *container) {
        if (datapoint == 1) {
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
                duration = benchmarkIteration<AVLTree<int>>(TINY_UNIFORM);
            }

            if (datasetStr == "medium") {
                duration = benchmarkIteration<AVLTree<int>>(MEDIUM_UNIFORM);
            }

            if (datasetStr == "large") {
                duration = benchmarkIteration<AVLTree<int>>(LARGE_UNIFORM);
            }
        } else if (variation == "sorted") {
            if (datasetStr == "tiny") {
                duration = benchmarkIteration<AVLTree<int>>(TINY_SORTED);
            }

            if (datasetStr == "medium") {
                duration = benchmarkIteration<AVLTree<int>>(MEDIUM_SORTED);
            }

            if (datasetStr == "large") {
                duration = benchmarkIteration<AVLTree<int>>(LARGE_SORTED);
            }
        } else {
            if (datasetStr == "tiny") {
                duration = benchmarkIteration<AVLTree<int>>(TINY_REVERSE);
            }

            if (datasetStr == "medium") {
                duration = benchmarkIteration<AVLTree<int>>(MEDIUM_REVERSE);
            }

            if (datasetStr == "large") {
                duration = benchmarkIteration<AVLTree<int>>(LARGE_REVERSE);
            }
        }
    } else {
        if (variation == "random") {
            if (datasetStr == "tiny") {
                duration = benchmarkIterationSet<>(TINY_UNIFORM);
            }

            if (datasetStr == "medium") {
                duration = benchmarkIterationSet<>(MEDIUM_UNIFORM);
            }

            if (datasetStr == "large") {
                duration = benchmarkIterationSet<>(LARGE_UNIFORM);
            }
        } else if (variation == "sorted") {
            if (datasetStr == "tiny") {
                duration = benchmarkIterationSet<>(TINY_SORTED);
            }

            if (datasetStr == "medium") {
                duration = benchmarkIterationSet<>(MEDIUM_SORTED);
            }

            if (datasetStr == "large") {
                duration = benchmarkIterationSet<>(LARGE_SORTED);
            }
        } else {
            if (datasetStr == "tiny") {
                duration = benchmarkIterationSet<>(TINY_REVERSE);
            }

            if (datasetStr == "medium") {
                duration = benchmarkIterationSet<>(MEDIUM_REVERSE);
            }

            if (datasetStr == "large") {
                duration = benchmarkIterationSet<>(LARGE_REVERSE);
            }
        }
    }
    std::cout << duration << "\n";
}
