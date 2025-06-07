#pragma once

#include "avl_tree/avl_tree.h"

template <typename T, typename Compare>
T &AVLTree<T, Compare>::Iterator::operator*() const {
    return nodeStack.top()->value;
}
template <typename T, typename Compare>
T *AVLTree<T, Compare>::Iterator::operator->() const {
    return &(nodeStack.top()->value);
}
template <typename T, typename Compare>
AVLTree<T, Compare>::Iterator &AVLTree<T, Compare>::Iterator::operator++() {
    Node *node = nodeStack.top();
    nodeStack.pop();
    if (node->right) {
        pushLeftNodes(node->right.get());
    }
    return *this;
};
template <typename T, typename Compare>
AVLTree<T, Compare>::Iterator AVLTree<T, Compare>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}
template <typename T, typename Compare>
bool AVLTree<T, Compare>::Iterator::operator==(
    const AVLTree<T, Compare>::Iterator &other) const {
    if (nodeStack.empty() && other.nodeStack.empty()) {
        return true;
    }
    if (nodeStack.empty() || other.nodeStack.empty()) {
        return false;
    }

    return nodeStack.top() == other.nodeStack.top();
}
template <typename T, typename Compare>
bool AVLTree<T, Compare>::Iterator::operator!=(
    const AVLTree<T, Compare>::Iterator &other) const {
    return !(*this == other);
}

template <typename T, typename Compare>
void AVLTree<T, Compare>::Iterator::pushLeftNodes(
    AVLTree<T, Compare>::Node *node) {
    while (node) {
        nodeStack.push(node);
        node = node->left.get();
    }
}
