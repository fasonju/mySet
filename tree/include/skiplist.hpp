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

// Search the skiplist for a value
// return the node if the value exists, else return a nullpointer
template <typename T, typename Compare>
T* SkipList<T, Compare>::search(const T& value) const {
    Node* current = _header;

    // start at highest express lane, go down a level when next node is
    // higher than node we are looking for
    for (int level = _currentLevel - 1; level >= 0; --level) {
        bool lessThan = comp(current->forward[level]->value, value);
        while (current->forward[level] && lessThan) {
            current = current->forward[level];
        }
    }

    current = current->forward[0];

    // Check if the found node equals the value
    bool equal = !comp(value, current->value) && !comp(current->value, value);
    if (current && equal) {
        return &current->value;
    }

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

// Look if a value exists in the skiplist
// return true if it exists, else return false
template <typename T, typename Compare>
bool SkipList<T, Compare>::contains(const T& value) const {
    Node* current = _header;

    // start at highest express lane, go down a level when next node is
    // higher than node we are looking for
    for (int level = _currentLevel - 1; level >= 0; --level) {
        bool lessThan = comp(current->forward[level]->value, value);
        while (current->forward[level] && lessThan) {
            current = current->forward[level];
        }
    }

    // next node is the one we are looking for
    current = current->forward[0];

    bool equal = !comp(value, current->value) && !comp(current->value, value);
    return current && equal;
}

// Clear the whole skiplist of its nodes and reset the header's pointers
template <typename T, typename Compare>
void SkipList<T, Compare>::clear() {
    Node* current = _header->forward[0];

    // delete all nodes by traversing lvl 0
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
