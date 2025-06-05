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
    // go all the way to the lowest layer of skiplist,
    // then run through until you reach a node that has no pointers out
    // return value of last node

    return nullptr;
}

template <typename T>
    requires std::totally_ordered<T>
T* SkipList<T>::min() const {
    // return the element after the dummy header

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
    // discard previous linked list,
    // start with new dummy header with value negative inf

    // empty
}

template <typename T>
    requires std::totally_ordered<T>
bool SkipList<T>::empty() const {
    // check if there is an element after dummy header
    // return true if there is none

    return true;
}

template <typename T>
    requires std::totally_ordered<T>
size_t SkipList<T>::size() const {
    // go all the way to the lowest layer of skiplist,
    // then run through and count the number of nodes
    // until you reach a node that has no pointers out

    return 0;
}

template <typename T>
    requires std::totally_ordered<T>
int SkipList<T>::randomLevel() {
    // flip a coin, if heads, increment by one and flip again
    // if tails, stop and return

    return 0;
}

template <typename T>
    requires std::totally_ordered<T>
typename SkipList<T>::Node* SkipList<T>::createNode(const T& value, int level) {
    // idk

    return new Node(value, level);
}
