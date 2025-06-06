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

// go all the way to the lowest layer of skiplist,
// then run through until you reach a node that has no pointers out
// return value of last node
template <typename T, typename Compare>
T* SkipList<T, Compare>::max() const {
    Node* x = _header;
    // Traverse as far as possible on level 0
    while (x->forward[0] != nullptr) {
        x = x->forward[0];
    }

    // If list is empty, x == _header, and x->forward[0] == nullptr
    return (x == _header) ? nullptr : &x->value;
}

// return the element after the dummy header
template <typename T, typename Compare>
T* SkipList<T, Compare>::min() const {
    Node* x = _header->forward[0];
    return x ? &x->value : nullptr;
}

template <typename T, typename Compare>
bool SkipList<T, Compare>::contains(const T& value) const {

    return true;
}

// Clear the whole skiplist of its nodes and reset the header's pointers
template <typename T, typename Compare>
void SkipList<T, Compare>::clear() {
    Node* current = _header->forward[0];

    // delete all nodes by traverding lvl 0
    while (current != nullptr) {
        Node* next = current->forward[0];
        delete current;
        current = next;
    }

    // reset header pointers
    for (auto& ptr : _header->forward) {
        ptr = nullptr;
    }

    _size = 0;
    _currentLevel = 1;
}

// check if there are elements in the skiplist (besides header)
template <typename T, typename Compare>
bool SkipList<T, Compare>::empty() const {
    return _size == 0; // no need for generic compare function
}

// return the number of elements in the skiplist
template <typename T, typename Compare>
size_t SkipList<T, Compare>::size() const {
    return _size;
}

// flip a coin, if heads, increment by one and flip again
// if tails, stop and return
template <typename T, typename Compare>
int SkipList<T, Compare>::randomLevel() {
    int level = 1;
    while (_dist(_gen) < 0.5 && level < _maxLevel)
        ++level;
    return level;
}

template <typename T, typename Compare>
typename SkipList<T, Compare>::Node* SkipList<T, Compare>::createNode(const T& value, int level) {
    return new Node(value, level);
}
