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
        node = std::make_unique<Node>(std::move(value));
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
    const int leftHeight = node->left ? node->left->height : 0;
    const int rightHeight = node->right ? node->right->height : 0;
    node->height = max(leftHeight, rightHeight) + 1;

    int balance = node->getBalance();

    // Left side
    if (balance > 1 && !valueBigger) {
        node->right_rotate();
    }

    if (balance > 1 && valueBigger) {
        node->left->left_rotate();
        node->right_rotate();
    }

    // Right side
    if (balance < 1 && valueBigger) {
        node->left_rotate();
    }

    if (balance < 1 && !valueBigger) {
        node->right->right_rotate();
        node->left_rotate();
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

    const int leftHeight = leftExists ? node->left->height : 0;
    const int rightHeight = rightExists ? node->right->height : 0;

    // base cases
    if (!leftExists && !rightExists) {
        node = nullptr;
    } else if (!leftExists) {
        node = std::move(node->right);
    } else if (!rightExists) {
        node = std::move(node->right);
    } else {
    }
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::remove(const T &value) {
    return remove(this->head, value);
}
