#pragma once

#include "container.h"
#include <__compare/compare_three_way.h>
#include <memory>

template <typename T, typename Compare = std::less<T>> class AVLTree {
  public:
    AVLTree() : head(nullptr) {};
    AVLTree(const AVLTree &) = delete;
    AVLTree(AVLTree &&) = delete;
    AVLTree &operator=(const AVLTree &) = delete;
    AVLTree &operator=(AVLTree &&) = delete;
    ~AVLTree() = default;

    // Insert a value into the tree
    bool insert(T value);

    // Remove a value from the tree
    bool remove(const T &value);

    /**
     * Search for a value in the tree
     *
     * returns nullptr if not found
     */
    [[nodiscard]] T *search(const T &value) const;

    // Get max value
    [[nodiscard]] T *max() const;

    // Get min value
    [[nodiscard]] T *min() const;

    // Check if the tree contains a specific value
    [[nodiscard]] bool contains(const T &value) const;

    // Get the height of the tree
    [[nodiscard]] int height() const;

    // Get the number of nodes
    [[nodiscard]] size_t size() const;

    // Clear the entire tree
    void clear();

    // Check if the tree is empty
    [[nodiscard]] bool empty() const;

  private:
    struct Node {
        T value;
        int height = 1;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(T &&value)
            : value(std::move(value)), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> head;

    bool insert(std::unique_ptr<Node> &node, T &&value);
    bool remove(std::unique_ptr<Node> &node, const T &value);
    [[nodiscard]] T *search(const std::unique_ptr<Node> &Node,
                            const T &value) const;
    [[nodiscard]] T *max(const std::unique_ptr<Node> &node) const;
    [[nodiscard]] T *min(const std::unique_ptr<Node> &node) const;
    [[nodiscard]] bool contains(const std::unique_ptr<Node> &node,
                                const T &value) const;
    [[nodiscard]] size_t size(const std::unique_ptr<Node> &node) const;
    [[nodiscard]] std::unique_ptr<Node> &
    getInOrderSuccessor(const std::unique_ptr<Node> &node) const;
    [[nodiscard]] int getBalance(const std::unique_ptr<Node> &node) const;
    void leftRotate(std::unique_ptr<Node> &node);
    void rightRotate(std::unique_ptr<Node> &node);
    void updateHeight(std::unique_ptr<Node> &node);
    Compare comp;
};

#include "pointer_avl_tree.hpp"

static_assert(Dontainer<AVLTree<int>, int>);
// static_assert(std::ranges::range<AVLTree<int>>);
