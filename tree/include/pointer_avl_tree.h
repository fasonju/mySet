#pragma once

#include "avl_tree.h"

template <typename T>
    requires std::totally_ordered<T>
class PointerAVLTree : AVLTree<T> {
  public:
    PointerAVLTree(const PointerAVLTree &) = delete;
    PointerAVLTree(PointerAVLTree &&) = delete;
    PointerAVLTree &operator=(const PointerAVLTree &) = delete;
    PointerAVLTree &operator=(PointerAVLTree &&) = delete;
    virtual ~PointerAVLTree() = default;

    // Insert a value into the tree
    virtual void insert(const T &value) = 0;

    // Remove a value from the tree
    virtual bool remove(const T &value) = 0;

    virtual bool removeAll(const T &value) = 0;

    /**
     * Search for a value in the tree
     *
     * returns nullptr if not found
     */
    virtual T *search(const T &value) const = 0;

    // Get max value
    virtual T *max() const = 0;

    // Get min value
    virtual T *min() const = 0;

    // Check if the tree contains a specific value
    virtual bool contains(const T &value) const = 0;

    // Get the height of the tree
    [[nodiscard]] virtual int height() const = 0;

    // Get the number of nodes
    [[nodiscard]] virtual size_t size() const = 0;

    // Clear the entire tree
    virtual void clear() = 0;

    // Check if the tree is empty
    [[nodiscard]] virtual bool empty() const = 0;
};
