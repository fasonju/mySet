#pragma once

#include "container.h"
#include <__compare/compare_three_way.h>
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

  public:
    AVLTree() : head(nullptr) {};
    AVLTree(const AVLTree &) = delete;
    AVLTree(AVLTree &&) = delete;
    AVLTree &operator=(const AVLTree &) = delete;
    AVLTree &operator=(AVLTree &&) = delete;
    ~AVLTree() = default;

    class Iterator {
      public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;   // or also value_type*
        using reference = T &; // or also value_type&

        explicit Iterator(Node *node) { pushLeftNodes(node); }

        reference operator*() const { return nodeStack.top()->value; }
        pointer operator->() const { return &(nodeStack.top()->value); }
        // increment operator ++ (you will need to implement traversal logic)
        Iterator &operator++() {
            Node *node = nodeStack.top();
            nodeStack.pop();
            if (node->right) {
                pushLeftNodes(node->right.get());
            }
            return *this;
        };
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const Iterator &other) const {
            if (nodeStack.empty() && other.nodeStack.empty()) {
                return true;
            }
            if (nodeStack.empty() || other.nodeStack.empty()) {
                return false;
            }

            return nodeStack.top() == other.nodeStack.top();
        }

        bool operator!=(const Iterator &other) const {
            return !(*this == other);
        }

      private:
        std::stack<Node *> nodeStack;
        void pushLeftNodes(Node *node) {
            while (node) {
                nodeStack.push(node);
                node = node->left.get();
            }
        }
    };

    [[nodiscard]] Iterator begin() const { return Iterator(head.get()); }
    [[nodiscard]] Iterator end() const { return Iterator(nullptr); };

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

#include "avl_tree/avl_tree.hpp"

static_assert(Dontainer<AVLTree<int>, int>);
// static_assert(std::ranges::range<AVLTree<int>>);
