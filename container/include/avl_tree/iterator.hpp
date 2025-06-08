#pragma once

#include "avl_tree/avl_tree.h"

template <typename T, typename Compare, typename Allocator>
T &AVLTree<T, Compare, Allocator>::Iterator::operator*() const {
    return nodeStack.top()->value;
}
template <typename T, typename Compare, typename Allocator>
T *AVLTree<T, Compare, Allocator>::Iterator::operator->() const {
    return &(nodeStack.top()->value);
}
template <typename T, typename Compare, typename Allocator>
AVLTree<T, Compare, Allocator>::Iterator &
AVLTree<T, Compare, Allocator>::Iterator::operator++() {
    Node *node = nodeStack.top();
    nodeStack.pop();
    if (node->right) {
        pushLeftNodes(node->right);
    }
    return *this;
};
template <typename T, typename Compare, typename Allocator>
AVLTree<T, Compare, Allocator>::Iterator
AVLTree<T, Compare, Allocator>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}
template <typename T, typename Compare, typename Allocator>
bool AVLTree<T, Compare, Allocator>::Iterator::operator==(
    const AVLTree<T, Compare, Allocator>::Iterator &other) const {
    if (nodeStack.empty() && other.nodeStack.empty()) {
        return true;
    }
    if (nodeStack.empty() || other.nodeStack.empty()) {
        return false;
    }

    return nodeStack.top() == other.nodeStack.top();
}
template <typename T, typename Compare, typename Allocator>
bool AVLTree<T, Compare, Allocator>::Iterator::operator!=(
    const AVLTree<T, Compare, Allocator>::Iterator &other) const {
    return !(*this == other);
}

template <typename T, typename Compare, typename Allocator>
void AVLTree<T, Compare, Allocator>::Iterator::pushLeftNodes(
    AVLTree<T, Compare, Allocator>::Node *node) {
    while (node) {
        nodeStack.push(node);
        node = node->left;
    }
}
