#pragma once

#include "container.h"
#include <memory>
#include <stack>

template <typename T, typename Compare = std::less<T>,
          typename Allocator = std::allocator<T>>
class AVLTree {
  private:
    struct Node {
        T value;
        int height = 1;
        Node *left;
        Node *right;

        explicit Node(T &&value)
            : value(std::move(value)), left(nullptr), right(nullptr) {}
    };

    using NodeAllocator =
        typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

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
    bool insert(T value) noexcept;
    /**
     * Removes and equivalent value from the tree, returns false if the value
     * does not exist in the tree.
     */
    bool remove(const T &value) noexcept;

    /**
     * Clear the tree.
     */
    void clear() noexcept;
    // access

    /**
     * Search for a value in the tree
     *
     * returns nullptr if not found
     */
    [[nodiscard]] T *search(const T &value) const noexcept;
    /**
     * Returns the max value in the tree, returns nullptr if the tree is empty.
     */

    [[nodiscard]] T *max() const noexcept;
    /**
     * Returns the min value in the tree, returns nullptr if the tree is empty.
     */
    [[nodiscard]] T *min() const noexcept;
    // Check if the tree contains a specific value
    [[nodiscard]] bool contains(const T &value) const noexcept;

    // info
    /**
     * Get the height of the tree.
     */
    [[nodiscard]] int height() const noexcept;
    /**
     * Returns the size of the tree
     */
    [[nodiscard]] size_t size() const noexcept;
    /**
     * Returns true if the tree is empty
     */
    [[nodiscard]] bool empty() const noexcept;

  private:
    Node *head;

    // modifiers
    bool insert(Node *&node, T &&value) noexcept;
    bool remove(Node *&node, const T &value) noexcept;
    /**
     * Remove a node, modify the pointer to point at one of their children or if
     * they have two children perform rotations.
     */
    void removeNode(Node *&node) noexcept;
    void clear(Node *node) noexcept;
    void leftRotate(Node *&node) noexcept;
    void rightRotate(Node *&node) noexcept;
    void updateHeight(Node *&node) noexcept;

    // access
    [[nodiscard]] T *search(Node *node, const T &value) const noexcept;
    [[nodiscard]] T *max(Node *node) const noexcept;
    [[nodiscard]] T *min(Node *node) const noexcept;
    [[nodiscard]] Node *minNode(Node *node) const noexcept;
    [[nodiscard]] bool contains(Node *node, const T &value) const noexcept;

    // info
    [[nodiscard]] size_t size(Node *node) const noexcept;
    [[nodiscard]] int getBalance(Node *node) const noexcept;
    Compare comp;
    NodeAllocator allocator;
};

#include "avl_tree/avl_tree.hpp"
#include "avl_tree/iterator.hpp" // IWYU pragma: keep

static_assert(Dontainer<AVLTree<int>, int>);
static_assert(std::ranges::range<AVLTree<int>>);
