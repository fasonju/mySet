#pragma once

#include "skiplist.h"

template <typename T>
    requires std::totally_ordered<T>
bool SkipList<T>::insert(T&& value) {

    return true;
}

template <typename T>
    requires std::totally_ordered<T>
bool SkipList<T>::remove(const T& value) {

    return true;
}

template <typename T>
    requires std::totally_ordered<T>
T* SkipList<T>::search(const T& value) const {

    return nullptr;
}

template <typename T>
    requires std::totally_ordered<T>
T* SkipList<T>::max() const {

    return nullptr;
}

template <typename T>
    requires std::totally_ordered<T>
T* SkipList<T>::min() const {

    return nullptr;
}

template <typename T>
    requires std::totally_ordered<T>
bool SkipList<T>::contains(const T& value) const {

    return true;
}

template <typename T>
    requires std::totally_ordered<T>
void SkipList<T>::clear() {

    // empty
}

template <typename T>
    requires std::totally_ordered<T>
bool SkipList<T>::empty() const {

    return true;
}

template <typename T>
    requires std::totally_ordered<T>
size_t SkipList<T>::size() const {

    return 0;
}

template <typename T>
    requires std::totally_ordered<T>
int SkipList<T>::randomLevel() {

    return 0;
}

template <typename T>
    requires std::totally_ordered<T>
typename SkipList<T>::Node* SkipList<T>::createNode(const T& value, int level) {

    return new Node(value, level);
}
