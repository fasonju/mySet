#pragma once

#include "skiplist.h"

template <typename T, typename Compare>
bool SkipList<T, Compare>::insert(T value) {

    return true;
}

template <typename T, typename Compare>
bool SkipList<T, Compare>::remove(const T& value) {

    return true;
}

template <typename T, typename Compare>
T* SkipList<T, Compare>::search(const T& value) const {

    return nullptr;
}

template <typename T, typename Compare>
T* SkipList<T, Compare>::max() const {
    // go all the way to the lowest layer of skiplist,
    // then run through until you reach a node that has no pointers out
    // return value of last node

    Node* x = _header;
    // Traverse as far as possible on level 0
    while (x->forward[0] != nullptr) {
        x = x->forward[0];
    }

    // If list is empty, x == _header, and x->forward[0] == nullptr
    return (x == _header) ? nullptr : &x->value;
}

template <typename T, typename Compare>
T* SkipList<T, Compare>::min() const {
    // return the element after the dummy header
    Node* x = _header->forward[0];
    return x ? &x->value : nullptr;
}

template <typename T, typename Compare>
bool SkipList<T, Compare>::contains(const T& value) const {

    return true;
}

template <typename T, typename Compare>
void SkipList<T, Compare>::clear() {
    // discard previous linked list,
    // start with new dummy header with value negative inf

    // empty
}

template <typename T, typename Compare>
bool SkipList<T, Compare>::empty() const {
    return _size == 0; // no need for generic compare function
}

template <typename T, typename Compare>
size_t SkipList<T, Compare>::size() const {
    return _size;
}

template <typename T, typename Compare>
int SkipList<T, Compare>::randomLevel() {
    // flip a coin, if heads, increment by one and flip again
    // if tails, stop and return
    int level = 1;
    while (_dist(_gen) < 0.5 && level < _maxLevel)
        ++level;
    return level;
}

template <typename T, typename Compare>
typename SkipList<T, Compare>::Node* SkipList<T, Compare>::createNode(const T& value, int level) {
    // idk

    return new Node(value, level);
}
