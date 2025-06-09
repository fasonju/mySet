#pragma once

#include "avl_tree/avl_tree.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <utility>

template <typename T, typename Compare, typename Allocator>
bool AVLTree<T, Compare, Allocator>::insert(Node *&node, T &&value) noexcept {
    if (node == nullptr) {
        Node *newNode = allocator.allocate(1);
        std::allocator_traits<NodeAllocator>::construct(allocator, newNode,
                                                        std::move(value));
        node = newNode;
        return true;
    }

    if (value == node->value) {
        return false;
    }

    const bool valueBigger = comp(node->value, value);

    if (valueBigger) {
        if (!insert(node->right, std::forward<T>(value))) {
            return false;
        };
    } else {
        if (!insert(node->left, std::forward<T>(value))) {
            return false;
        };
    }

    // update height
    updateHeight(node);

    int balance = getBalance(node);

    const bool subTreeRight =
        ((valueBigger && node->right && comp(node->right->value, value)) ||
         (!valueBigger && node->left && comp(node->left->value, value)));

    // Left side
    if (balance > 1 && !subTreeRight) {
        rightRotate(node);
    }

    if (balance > 1 && subTreeRight) {
        leftRotate(node->left);
        rightRotate(node);
    }

    // Right side
    if (balance < -1 && subTreeRight) {
        leftRotate(node);
    }

    if (balance < -1 && !subTreeRight) {
        rightRotate(node->right);
        leftRotate(node);
    }

    return true;
}

template <typename T, typename Compare, typename Allocator>
bool AVLTree<T, Compare, Allocator>::insert(T value) noexcept {
    return insert(this->head, std::forward<T>(value));
}

template <typename T, typename Compare, typename Allocator>
bool AVLTree<T, Compare, Allocator>::remove(Node *&node,
                                            const T &value) noexcept {
    if (node == nullptr) {
        return false;
    }

    if (comp(node->value, value)) {
        if (!remove(node->right, value)) {
            return false;
        }
    } else if (comp(value, node->value)) {
        if (!remove(node->left, value)) {
            return false;
        }
    } else {
        // removal logic
        if (!node->left && !node->right) {
            std::allocator_traits<NodeAllocator>::destroy(allocator, node);
            allocator.deallocate(node, 1);
            node = nullptr;
            return true;
        }

        if (!node->left) {
            Node *temp = node->right;
            std::allocator_traits<NodeAllocator>::destroy(allocator, node);
            allocator.deallocate(node, 1);
            node = temp;
        } else if (!node->right) {

            Node *temp = node->left;
            std::allocator_traits<NodeAllocator>::destroy(allocator, node);
            allocator.deallocate(node, 1);
            node = temp;
        } else {
            removeNode(node);
        }
    }

    // rebalancing and height update
    const bool leftExists = node->left != nullptr;
    const bool rightExists = node->right != nullptr;

    updateHeight(node);

    const int balance = getBalance(node);

    if (balance > 1 && leftExists && getBalance(node->left) >= 0) {
        rightRotate(node);
    } else if (balance < -1 && rightExists && getBalance(node->right) <= 0) {
        leftRotate(node);
    } else if (balance > 1 && leftExists && getBalance(node->left) < 0) {
        leftRotate(node->left);
        rightRotate(node);
    } else if (balance < -1 && rightExists && getBalance(node->right) > 0) {
        rightRotate(node->right);
        leftRotate(node);
    }

    return true;
}

template <typename T, typename Compare, typename Allocator>
void AVLTree<T, Compare, Allocator>::removeNode(Node *&node) noexcept {
    Node *successorParent = node;
    Node *successor = node->right;

    // Find in-order successor and its parent
    while (successor->left != nullptr) {
        successorParent = successor;
        successor = successor->left;
    }

    // Unlink the successor from its current location
    if (successorParent != node) {
        successorParent->left = successor->right;
        successor->right = node->right;
    }

    // Transfer left child
    successor->left = node->left;

    // Delete current node
    std::allocator_traits<NodeAllocator>::destroy(allocator, node);
    allocator.deallocate(node, 1);

    // Replace with successor
    node = successor;
}

template <typename T, typename Compare, typename Allocator>
bool AVLTree<T, Compare, Allocator>::remove(const T &value) noexcept {
    return remove(this->head, value);
}

template <typename T, typename Compare, typename Allocator>
T *AVLTree<T, Compare, Allocator>::search(const T &value) const noexcept {
    return search(this->head, value);
}

template <typename T, typename Compare, typename Allocator>
T *AVLTree<T, Compare, Allocator>::search(Node *node,
                                          const T &value) const noexcept {
    if (node == nullptr) {
        return nullptr;
    }

    if (!comp(node->value, value) && !comp(value, node->value)) {
        return &(node->value);
    }

    if (comp(value, node->value)) {
        return search(node->left, value);
    }
    return search(node->right, value);
}

template <typename T, typename Compare, typename Allocator>
T *AVLTree<T, Compare, Allocator>::max() const noexcept {
    if (this->head == nullptr) {
        return nullptr;
    }

    return max(this->head);
}

template <typename T, typename Compare, typename Allocator>
T *AVLTree<T, Compare, Allocator>::max(Node *node) const noexcept {
    return node->right ? max(node->right) : &node->value;
}

template <typename T, typename Compare, typename Allocator>
T *AVLTree<T, Compare, Allocator>::min() const noexcept {
    if (this->head == nullptr) {
        return nullptr;
    }

    return min(this->head);
}

template <typename T, typename Compare, typename Allocator>
AVLTree<T, Compare, Allocator>::Node *
AVLTree<T, Compare, Allocator>::minNode(Node *node) const noexcept {
    return node->left ? minNode(node->left) : node;
}

template <typename T, typename Compare, typename Allocator>
T *AVLTree<T, Compare, Allocator>::min(Node *node) const noexcept {
    return node->left ? min(node->left) : &node->value;
}

template <typename T, typename Compare, typename Allocator>
bool AVLTree<T, Compare, Allocator>::contains(const T &value) const noexcept {
    return contains(this->head, value);
}

template <typename T, typename Compare, typename Allocator>
bool AVLTree<T, Compare, Allocator>::contains(Node *node,
                                              const T &value) const noexcept {
    if (node == nullptr) {
        return false;
    }

    if (!comp(node->value, value) && !comp(value, node->value)) {
        return true;
    }

    if (comp(value, node->value)) {
        return contains(node->left, value);
    }

    return contains(node->right, value);
}

template <typename T, typename Compare, typename Allocator>
int AVLTree<T, Compare, Allocator>::height() const noexcept {
    return this->head ? this->head->height : 0;
}

template <typename T, typename Compare, typename Allocator>
size_t AVLTree<T, Compare, Allocator>::size() const noexcept {
    return size(this->head);
}

template <typename T, typename Compare, typename Allocator>
size_t AVLTree<T, Compare, Allocator>::size(Node *node) const noexcept {
    if (node == nullptr) {
        return 0;
    }

    return size(node->left) + size(node->right) + 1;
}

template <typename T, typename Compare, typename Allocator>
void AVLTree<T, Compare, Allocator>::clear() noexcept {
    clear(this->head);
    this->head = nullptr;
}

template <typename T, typename Compare, typename Allocator>
void AVLTree<T, Compare, Allocator>::clear(Node *node) noexcept {
    if (node == nullptr) {
        return;
    }
    clear(node->left);
    clear(node->right);
    std::allocator_traits<NodeAllocator>::destroy(allocator, node);
    allocator.deallocate(node, 1);
}

template <typename T, typename Compare, typename Allocator>
bool AVLTree<T, Compare, Allocator>::empty() const noexcept {
    return this->head == nullptr;
}

template <typename T, typename Compare, typename Allocator>
int AVLTree<T, Compare, Allocator>::getBalance(Node *node) const noexcept {
    const int leftHeight = node->left ? node->left->height : 0;
    const int rightHeight = node->right ? node->right->height : 0;

    return leftHeight - rightHeight;
}

template <typename T, typename Compare, typename Allocator>
void AVLTree<T, Compare, Allocator>::leftRotate(Node *&node) noexcept {
    if (node == nullptr || node->right == nullptr) {
        return;
    }

    Node *newRoot = node->right;
    // Move the left subtree of newRoot into the right subtree of root
    node->right = newRoot->left;
    // Make the old root the left child of newRoot
    newRoot->left = node;
    node = newRoot;
    updateHeight(node->left);
    updateHeight(node);
}

template <typename T, typename Compare, typename Allocator>
void AVLTree<T, Compare, Allocator>::rightRotate(Node *&node) noexcept {
    if (node == nullptr || node->left == nullptr) {
        return;
    }

    // Take ownership of the left child
    Node *newRoot = node->left;
    // Move the right subtree of newRoot into the left subtree of node
    node->left = newRoot->right;
    // Make the old root the right child of newRoot
    newRoot->right = node;
    // Update node to point to new root
    node = newRoot;
    updateHeight(node->right);
    updateHeight(node);
}

template <typename T, typename Compare, typename Allocator>
void AVLTree<T, Compare, Allocator>::updateHeight(Node *&node) noexcept {
    const bool leftExists = node->left != nullptr;
    const bool rightExists = node->right != nullptr;

    const int leftHeight = leftExists ? node->left->height : 0;
    const int rightHeight = rightExists ? node->right->height : 0;
    node->height = std::max(leftHeight, rightHeight) + 1;
}

template <typename T, typename Compare, typename Allocator>
AVLTree<T, Compare, Allocator>::Iterator
AVLTree<T, Compare, Allocator>::begin() const {
    return Iterator(this->head);
}

template <typename T, typename Compare, typename Allocator>
AVLTree<T, Compare, Allocator>::Iterator
AVLTree<T, Compare, Allocator>::end() const {
    return Iterator();
}
