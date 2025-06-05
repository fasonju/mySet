#pragma once

#include "avl_tree/pointer_avl_tree.h"
#include "log.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T, typename Compare>
bool AVLTree<T, Compare>::insert(std::unique_ptr<Node> &node, T &&value) {
    if (!node) {
        node = std::make_unique<Node>(std::move(value));
        return true;
    }

    if (value == node->value) {
        return false;
    }

    const bool valueBigger = comp(node->value, value);
    const bool subTreeRight =
        (valueBigger && node->right && comp(node->right->value, value) ||
         (!valueBigger && node->left && comp(node->left->value, value)));

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

template <typename T, typename Compare>
bool AVLTree<T, Compare>::insert(T value) {
    return insert(this->head, std::forward<T>(value));
}

template <typename T, typename Compare>
bool AVLTree<T, Compare>::remove(std::unique_ptr<Node> &node, const T &value) {
    if (!node) {
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
            node = nullptr;
            return true;
        }

        if (!node->left) {
            node = std::move(node->right);
        } else if (!node->right) {
            node = std::move(node->left);
        } else {
            std::unique_ptr<Node> &inorderSuccessor = getInOrderSuccessor(node);
            auto successorValue = inorderSuccessor->value; // Copy
            std::unique_ptr<Node> newNode =
                std::make_unique<Node>(std::move(successorValue));

            remove(node->right, inorderSuccessor->value);
            node = std::move(newNode);
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

template <typename T, typename Compare>
bool AVLTree<T, Compare>::remove(const T &value) {
    return remove(this->head, value);
}

template <typename T, typename Compare>
T *AVLTree<T, Compare>::search(const T &value) const {
    return search(this->head, value);
}

template <typename T, typename Compare>
T *AVLTree<T, Compare>::search(const std::unique_ptr<Node> &node,
                               const T &value) const {
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

template <typename T, typename Compare> T *AVLTree<T, Compare>::max() const {
    if (!this->head) {
        return nullptr;
    }

    return max(this->head);
}

template <typename T, typename Compare>
T *AVLTree<T, Compare>::max(const std::unique_ptr<Node> &node) const {
    return node->right ? max(node->right) : &node->value;
}

template <typename T, typename Compare> T *AVLTree<T, Compare>::min() const {
    if (!this->head) {
        return nullptr;
    }

    return min(this->head);
}

template <typename T, typename Compare>
T *AVLTree<T, Compare>::min(const std::unique_ptr<Node> &node) const {
    return node->left ? max(node->left) : &node->value;
}

template <typename T, typename Compare>
bool AVLTree<T, Compare>::contains(const T &value) const {
    return contains(this->head, value);
}

template <typename T, typename Compare>
bool AVLTree<T, Compare>::contains(const std::unique_ptr<Node> &node,
                                   const T &value) const {
    if (!node) {
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

template <typename T, typename Compare>
int AVLTree<T, Compare>::height() const {
    return this->head ? this->head->height : 0;
}

template <typename T, typename Compare>
size_t AVLTree<T, Compare>::size() const {
    return size(this->head);
}

template <typename T, typename Compare>
size_t AVLTree<T, Compare>::size(const std::unique_ptr<Node> &node) const {
    if (!node) {
        return 0;
    }

    return size(node->left) + size(node->right) + 1;
}

template <typename T, typename Compare> void AVLTree<T, Compare>::clear() {
    this->head = nullptr;
}

template <typename T, typename Compare>
bool AVLTree<T, Compare>::empty() const {
    return !this->head;
}

template <typename T, typename Compare>
int AVLTree<T, Compare>::getBalance(const std::unique_ptr<Node> &node) const {
    const int leftHeight = node->left ? node->left->height : 0;
    const int rightHeight = node->right ? node->right->height : 0;
    return leftHeight - rightHeight;
}

template <typename T, typename Compare>
void AVLTree<T, Compare>::leftRotate(std::unique_ptr<Node> &node) {
    if (!node || !node->right) {
        return;
    }

    std::unique_ptr<Node> newRoot = std::move(node->right);
    // Move the left subtree of newRoot into the right subtree of root
    node->right = std::move(newRoot->left);
    // Make the old root the left child of newRoot
    newRoot->left = std::move(node);
    node = std::move(newRoot);
    updateHeight(node->left);
    updateHeight(node);
}

template <typename T, typename Compare>
void AVLTree<T, Compare>::rightRotate(std::unique_ptr<Node> &node) {
    if (!node || !node->left) {
        return;
    }

    // Take ownership of the left child
    std::unique_ptr<Node> newRoot = std::move(node->left);
    // Move the right subtree of newRoot into the left subtree of node
    node->left = std::move(newRoot->right);
    // Make the old root the right child of newRoot
    newRoot->right = std::move(node);
    // Update node to point to new root
    node = std::move(newRoot);
    updateHeight(node->right);
    updateHeight(node);
}

/**
 * Assumes right subtree exists
 */
template <typename T, typename Compare>
std::unique_ptr<typename AVLTree<T, Compare>::Node> &
AVLTree<T, Compare>::getInOrderSuccessor(
    const std::unique_ptr<Node> &node) const {
    if (!node || !node->right) {
        LOG_ERROR("invalid argument");
        throw std::invalid_argument(
            "developer fault, inorderSuccessor must have right child");
    }

    auto *current = const_cast<std::unique_ptr<Node> *>(&node->right);
    while ((*current)->left) {
        current = &(*current)->left;
    }

    return *current;
}

template <typename T, typename Compare>
void AVLTree<T, Compare>::updateHeight(std::unique_ptr<Node> &node) {
    const bool leftExists = node->left != nullptr;
    const bool rightExists = node->right != nullptr;

    const int leftHeight = leftExists ? node->left->height : 0;
    const int rightHeight = rightExists ? node->right->height : 0;
    node->height = std::max(leftHeight, rightHeight) + 1;
}
