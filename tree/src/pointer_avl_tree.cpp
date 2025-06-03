#include "pointer_avl_tree.h"
#include "log.h"
#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <utility>

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::insert(std::unique_ptr<Node> &node, T &&value) {
    if (!node) {
        this->head = std::make_unique<Node>(std::move(value));
    }

    if (value == node->value) {
        LOG_ERROR("Duplicate value");
        return false;
    }

    const bool valueBigger = value > node->value;

    if (valueBigger) {
        if (!insert(node->right, std::move(value))) {
            return false;
        }
    } else {
        if (!insert(node->left, std::move(value))) {
            return false;
        }
    }

    // update height
    const int leftHeight = node->left ? node->left->height : -1;
    const int rightHeight = node->right ? node->right->height : -1;
    node->height = max(leftHeight, rightHeight) + 1;

    int balance = this->left->height - this->right->height;

    // Left side
    if (balance > 1 && !valueBigger) {
        this->right_rotate();
    }

    if (balance > 1 && valueBigger) {
        this->left->left_rotate();
        this->right_rotate();
    }

    // Right side
    if (balance < 1 && valueBigger) {
        this->left_rotate();
    }

    if (balance < 1 && !valueBigger) {
        this->right->right_rotate();
        this->left_rotate();
    }

    return true;
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::insert(T &&value) {
    return insert(this->head, std::move(value));
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
    }

    // removal and rebalancing logic
    const bool leftExists = node->left;
    const bool rightExists = node->right;

    const int leftHeight = leftExists ? node->left->height : -1;
    const int rightHeight = rightExists ? node->right->height : -1;

    // base cases
    if (!leftExists && !rightExists) {
        node = nullptr;
        return true;
    }
    if (!leftExists) {
        node = std::move(node->right);
        return true;
    }
    if (!rightExists) {
        node = std::move(node->right);
        return true;
    }
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::remove(const T &value) {
    return remove(this->head, value);
}
