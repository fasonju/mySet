#include "pointer_avl_tree.h"
#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <memory>

template <typename T>
    requires std::totally_ordered<T>
void PointerAVLTree<T>::Node::fixImbalance(bool valueBigger) {
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
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::insert(std::unique_ptr<Node> &node, T &&value) {
    if (!node) {
        this->head = std::make_unique<Node>(std::move(value));
    }

    if (value == node->value) {
        return false;
    }

    bool valueBigger = value > node->value;

    if (valueBigger) {
        insert(node->right, std::move(value));
    } else {
        insert(node->left, std::move(value));
    }

    // update height
    node->height = max(node->left->height, node->right->height) + 1;

    node->fixImbalance(valueBigger);

    return true;
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::insert(T &&value) {
    return insert(this->head, std::move(value));
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::remove(const T &value) {
    return remove(this->head, value);
}
