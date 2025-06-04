#pragma once

#include "avl_tree.h"
#include <memory>

template <typename T>
    requires std::totally_ordered<T>
class PointerAVLTree : AVLTree<T> {
  public:
    PointerAVLTree(const PointerAVLTree &) = delete;
    PointerAVLTree(PointerAVLTree &&) = delete;
    PointerAVLTree &operator=(const PointerAVLTree &) = delete;
    PointerAVLTree &operator=(PointerAVLTree &&) = delete;
    ~PointerAVLTree() = default;

    // Insert a value into the tree
    bool insert(T &&value) override;

    // Remove a value from the tree
    bool remove(const T &value) override;

    /**
     * Search for a value in the tree
     *
     * returns nullptr if not found
     */
    T *search(const T &value) const override;

    // Get max value
    T *max() const override;

    // Get min value
    T *min() const override;

    // Check if the tree contains a specific value
    bool contains(const T &value) const override;

    // Get the height of the tree
    [[nodiscard]] int height() const override;

    // Get the number of nodes
    [[nodiscard]] size_t size() const override;

    // Clear the entire tree
    void clear() override;

    // Check if the tree is empty
    [[nodiscard]] bool empty() const override;

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
    T *search(const std::unique_ptr<Node> &Node, const T &value) const;
    T *max(const std::unique_ptr<Node> &node) const;
    T *min(const std::unique_ptr<Node> &node) const;
    bool contains(const std::unique_ptr<Node> &node, const T &value) const;
    size_t size(const std::unique_ptr<Node> &node) const;
    std::unique_ptr<Node> &
    getInorderSuccessor(const std::unique_ptr<Node> &node) const;
    int getBalance(const std::unique_ptr<Node> &node) const;
    void left_rotate(std::unique_ptr<Node> &node);  // TODO(jasonfu): implement
    void right_rotate(std::unique_ptr<Node> &Node); // TODO(jasonfu): implement
};
