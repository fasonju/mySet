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

    bool removeAll(const T &value) override;

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
        int height{};
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        explicit Node(T &&value)
            : value(std::move(value)), left(nullptr), right(nullptr) {}

        int getBalanceFactor();
    };

    std::unique_ptr<Node> &head;

    void insert(std::unique_ptr<Node> &node, T &&value);
};
