#pragma once

#include "log.h"
#include "pointer_avl_tree.h"
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <memory>
#include <stdexcept>
#include <utility>

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::insert(std::unique_ptr<Node> &node, T &&value) {
    if (!node) {
        node = std::make_unique<Node>(std::move(value));
        return true;
    }

    if (value == node->value) {
        throw std::invalid_argument("Duplicate key");
    }

    const bool valueBigger = value > node->value;
    bool treeGrew = false;

    if (valueBigger) {
        const bool subtreeGrew = insert(node->right, std::forward<T>(value));
        treeGrew = subtreeGrew &&
                   ((node->left && node->left->height < node->right->height) ||
                    !node->left);
    } else {
        const bool subtreeGrew = insert(node->left, std::forward<T>(value));
        treeGrew = subtreeGrew &&
                   ((node->right && node->right->height < node->left->height) ||
                    !node->right);
    }

    // update height
    const int leftHeight = node->left ? node->left->height : 0;
    const int rightHeight = node->right ? node->right->height : 0;
    node->height =
        std::max(leftHeight, rightHeight) + static_cast<int>(treeGrew);

    int balance = getBalance(node);

    // Left side
    if (balance > 1 && !valueBigger) {
        rightRotate(node);
    }

    if (balance > 1 && valueBigger) {
        leftRotate(node->left);
        rightRotate(node);
    }

    // Right side
    if (balance < -1 && valueBigger) {
        leftRotate(node);
    }

    if (balance < -1 && !valueBigger) {
        rightRotate(node->right);
        leftRotate(node);
    }

    return treeGrew;
}

template <typename T>
    requires std::totally_ordered<T>
// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
bool PointerAVLTree<T>::insert(T &&value) {
    try {
        insert(this->head, std::forward<T>(value));
        return true;
    } catch (std::exception &exception) {
        LOG_ERROR(exception.what());
        return false;
    }
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::remove(std::unique_ptr<Node> &node, const T &value) {
    if (!node) {
        return false;
    }

    if (value > node->value) {
        if (!remove(node->right, value)) {
            return false;
        }
    } else if (value < node->value) {
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

    const int leftHeight = leftExists ? node->left->height : 0;
    const int rightHeight = rightExists ? node->right->height : 0;
    node->height = std::max(leftHeight, rightHeight);

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

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::remove(const T &value) {
    return remove(this->head, value);
}

template <typename T>
    requires std::totally_ordered<T>
T *PointerAVLTree<T>::search(const T &value) const {
    return search(this->head, value);
}

template <typename T>
    requires std::totally_ordered<T>
T *PointerAVLTree<T>::search(const std::unique_ptr<Node> &node,
                             const T &value) const {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->value == value) {
        return &(node->value);
    }

    if (value < node->value) {
        return search(node->left, value);
    }
    return search(node->right, value);
}

template <typename T>
    requires std::totally_ordered<T>
T *PointerAVLTree<T>::max() const {
    if (!this->head) {
        return nullptr;
    }

    return max(this->head);
}

template <typename T>
    requires std::totally_ordered<T>
T *PointerAVLTree<T>::max(const std::unique_ptr<Node> &node) const {
    return node->right ? max(node->right) : &node->value;
}

template <typename T>
    requires std::totally_ordered<T>
T *PointerAVLTree<T>::min() const {
    if (!this->head) {
        return nullptr;
    }

    return min(this->head);
}

template <typename T>
    requires std::totally_ordered<T>
T *PointerAVLTree<T>::min(const std::unique_ptr<Node> &node) const {
    return node->left ? max(node->left) : &node->value;
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::contains(const T &value) const {
    return contains(this->head, value);
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::contains(const std::unique_ptr<Node> &node,
                                 const T &value) const {
    if (!node) {
        return false;
    }

    if (value == node->value) {
        return true;
    }

    if (value < node->value) {
        return contains(node->left, value);
    }

    return contains(node->right, value);
}

template <typename T>
    requires std::totally_ordered<T>
int PointerAVLTree<T>::height() const {
    return this->head ? this->head->height : 0;
}

template <typename T>
    requires std::totally_ordered<T>
size_t PointerAVLTree<T>::size() const {
    return size(this->head);
}

template <typename T>
    requires std::totally_ordered<T>
size_t PointerAVLTree<T>::size(const std::unique_ptr<Node> &node) const {
    if (!node) {
        return 0;
    }

    return size(node->left) + size(node->right) + 1;
}

template <typename T>
    requires std::totally_ordered<T>
void PointerAVLTree<T>::clear() {
    this->head = nullptr;
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::empty() const {
    return !this->head;
}

template <typename T>
    requires std::totally_ordered<T>
int PointerAVLTree<T>::getBalance(const std::unique_ptr<Node> &node) const {
    const int leftHeight = node->left ? node->left->height : 0;
    const int rightHeight = node->right ? node->right->height : 0;
    return leftHeight - rightHeight;
}

template <typename T>
    requires std::totally_ordered<T>
void PointerAVLTree<T>::leftRotate(std::unique_ptr<Node> &node) {
    if (!node || !node->right) {
        return;
    }

    std::unique_ptr<Node> newRoot = std::move(node->right);

    // Move the left subtree of newRoot into the right subtree of root
    node->right = std::move(newRoot->left);

    // Make the old root the left child of newRoot
    newRoot->left = std::move(node);

    node = std::move(newRoot);
}

template <typename T>
    requires std::totally_ordered<T>
void PointerAVLTree<T>::rightRotate(std::unique_ptr<Node> &node) {
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
}

/**
 * Assumes right subtree exists
 */
template <typename T>
    requires std::totally_ordered<T>
std::unique_ptr<typename PointerAVLTree<T>::Node> &
PointerAVLTree<T>::getInOrderSuccessor(
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
