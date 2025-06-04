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
        return true;
    }

    if (value == node->value) {
        LOG_ERROR("Duplicate value");
        return false;
    }

    const bool valueBigger = value > node->value;
    bool treeGrew = false;

    if (valueBigger) {
        const bool subtreeGrew = insert(node->right, std::forward(value));
        treeGrew = subtreeGrew &&
                   ((node->left && node->left->height < node->right->height) ||
                    !node->left);
    } else {
        const bool subtreeGrew = insert(node->left, std::forward(value));
        treeGrew = subtreeGrew &&
                   ((node->right && node->right->height < node->left->height) ||
                    !node->right);
    }

    // update height
    const int leftHeight = node->left ? node->left->height : 0;
    const int rightHeight = node->right ? node->right->height : 0;
    node->height = max(leftHeight, rightHeight) + treeGrew;

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
    if (balance < -1 && valueBigger) {
        node->left_rotate();
    }

    if (balance < -1 && !valueBigger) {
        node->right->right_rotate();
        node->left_rotate();
    }

    return treeGrew;
}

template <typename T>
    requires std::totally_ordered<T>
// NOLINTNEXTLINE(cppcoreguidelines-rvalue-reference-param-not-moved)
bool PointerAVLTree<T>::insert(T &&value) {
    return insert(this->head, std::forward<T>(value));
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
            node == nullptr;
            return true;
        }

        if (!node->left) {
            node = std::move(node->right);
        } else if (!node->right) {
            node = std::move(node->left);
        } else {

            std::unique_ptr<Node> &inorderSuccessor =
                node->getInorderSuccessor();
            std::unique_ptr<Node> newNode =
                std::make_unique<Node>(inorderSuccessor->value);
            remove(node->right, inorderSuccessor->value);
            node = std::move(newNode);
        }
    }

    // rebalancing and height update
    const bool leftExists = node->left;
    const bool rightExists = node->right;

    const int leftHeight = leftExists ? node->left->height : 0;
    const int rightHeight = rightExists ? node->right->height : 0;
    node->height = max(leftHeight, rightHeight);

    const int balance = node->getBalance();

    if (balance > 1 && leftExists && node->left->getBalance() >= 0) {
        node->right_rotate();
    } else if (balance < -1 && rightExists && node->right->getBalance <= 0) {
        node->left_rotate();
    } else if (balance > 1 && leftExists && node->left->getBalance() < 0) {
        node->left->left_rotate();
        node->right_rotate();
    } else if (balance < -1 && rightExists && node->right->getBalance > 0) {
        node->right->right_rotate();
        node->left_rotate();
    }

    return true;
}

template <typename T>
    requires std::totally_ordered<T>
bool PointerAVLTree<T>::remove(const T &value) {
    return remove(this->head, value);
}
