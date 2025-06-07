#pragma once

#include "container.h"
#include <memory>
#include <stack>

template <typename T, typename Compare = std::less<T>> class AVLTree {
  private:
    struct Node {
        T value;
        int height = 1;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(T &&value)
            : value(std::move(value)), left(nullptr), right(nullptr) {}
    };

    struct NodeDeleter {
        void operator()(Node *ptr) const {
            if (ptr) {
                // Instead of `delete ptr`, return memory to your pool allocator
                poolDeallocate(ptr);
            }
        }
    };

  public:
    AVLTree() : head(nullptr) {};
    AVLTree(const AVLTree &) = delete;
    AVLTree(AVLTree &&) = delete;
    AVLTree &operator=(const AVLTree &) = delete;
    AVLTree &operator=(AVLTree &&) = delete;
    ~AVLTree() = default;

    // iterator
    class Iterator {
      public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;   // or also value_type*
        using reference = T &; // or also value_type&

        Iterator() = default;
        explicit Iterator(Node *node) { pushLeftNodes(node); }

        reference operator*() const;
        pointer operator->() const;

        Iterator &operator++();
        Iterator operator++(int);
        bool operator==(const Iterator &other) const;

        bool operator!=(const Iterator &other) const;

      private:
        std::stack<Node *> nodeStack;
        /**
         * Push current nodes and all nodes in preorder into the stack, however
         * stop when a leaf is reached. Equivalent to recursively pushing the
         * left node.
         */
        void pushLeftNodes(Node *node);
    };

    [[nodiscard]] Iterator begin() const;
    [[nodiscard]] Iterator end() const;

    // modifiers

    /**
     * Copies the value into the tree and inserts it. Returns false if the value
     * already existed in the tree.
     */
    bool insert(T value);
    /**
     * Removes and equivalent value from the tree, returns false if the value
     * does not exist in the tree.
     */
    bool remove(const T &value);

    /**
     * Clear the tree.
     */
    void clear();
    // access

    /**
     * Search for a value in the tree
     *
     * returns nullptr if not found
     */
    [[nodiscard]] T *search(const T &value) const;
    /**
     * Returns the max value in the tree, returns nullptr if the tree is empty.
     */

    [[nodiscard]] T *max() const;
    /**
     * Returns the min value in the tree, returns nullptr if the tree is empty.
     */
    [[nodiscard]] T *min() const;
    // Check if the tree contains a specific value
    [[nodiscard]] bool contains(const T &value) const;

    // info
    /**
     * Get the height of the tree.
     */
    [[nodiscard]] int height() const;
    /**
     * Returns the size of the tree
     */
    [[nodiscard]] size_t size() const;
    /**
     * Returns true if the tree is empty
     */
    [[nodiscard]] bool empty() const;

  private:
    std::unique_ptr<Node> head;

    // modifiers
    bool insert(std::unique_ptr<Node> &node, T &&value);
    bool remove(std::unique_ptr<Node> &node, const T &value);
    void leftRotate(std::unique_ptr<Node> &node);
    void rightRotate(std::unique_ptr<Node> &node);
    void updateHeight(std::unique_ptr<Node> &node);

    // access
    [[nodiscard]] T *search(const std::unique_ptr<Node> &Node,
                            const T &value) const;
    [[nodiscard]] T *max(const std::unique_ptr<Node> &node) const;
    [[nodiscard]] T *min(const std::unique_ptr<Node> &node) const;
    [[nodiscard]] bool contains(const std::unique_ptr<Node> &node,
                                const T &value) const;
    [[nodiscard]] std::unique_ptr<Node> &
    getInOrderSuccessor(const std::unique_ptr<Node> &node) const;

    // info
    [[nodiscard]] size_t size(const std::unique_ptr<Node> &node) const;
    [[nodiscard]] int getBalance(const std::unique_ptr<Node> &node) const;
    Compare comp;
};

#include "avl_tree/avl_tree.hpp"
#include "avl_tree/iterator.hpp" // IWYU pragma: keep

static_assert(Dontainer<AVLTree<int>, int>);
static_assert(std::ranges::range<AVLTree<int>>);
