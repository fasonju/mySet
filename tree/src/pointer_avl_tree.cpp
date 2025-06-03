#include "pointer_avl_tree.h"
#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <memory>

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::insert(std::unique_ptr<Node> &node, T &&value) {
    if (!node) {
        this->head = std::make_unique<Node>(std::move(value));
    }
    bool valueBigger = value > node->value;
    bool valueSmaller = value < node->value;

    if (valueSmaller) {
        insert(node.left, std::move(value));
    } else if (valueBigger) {
        insert(node->right, std::move(value));
    } else {
        return false;
    }

    // update height
    node->height = max(node->left->height, node->right->height) + 1;

    int balance = node->left->height - node->right->height;

    // Left side
    if (balance > 1 && valueSmaller) {
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

    if (balance < 1 && valueSmaller) {
        node->right->right_rotate();
        node->left_rotate();
    }
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::insert(T &&value) {
    return insert(this->head, std::move(value));
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::remove(const T &value) {}
