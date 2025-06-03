#include "pointer_avl_tree.h"
#include "log.h"
#include <concepts>
#include <cstddef>
#include <cstdlib>

template <typename T>
    requires std::totally_ordered<T>
void PointerAVLTree<T>::insert(T value) {
    if (this->head == nullptr) {
        this->head = Node{.value = value, .left = nullptr, .right = nullptr};
    }

    LOG_ERROR("insert not implemented");
    std::exit(1); // NOLINT(concurrency-mt-unsafe)
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::remove(const T &value) {}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::removeAll(const T &value) {}
