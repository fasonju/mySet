#pragma once

#include <functional>
#include <optional>
#include <vector>

template <typename Value, typename Compare = std::less<Value>> class AVLTree {
public:
  virtual ~AVLTree() = default;

  // Insert a value into the tree
  virtual void insert(const Value &value) = 0;

  // Remove a value from the tree
  virtual bool remove(const Value &value) = 0;

  // Search for a value in the tree
  virtual std::optional<Value> search(const Value &value) const = 0;

  // Check if the tree contains a specific value
  virtual bool contains(const Value &value) const = 0;

  // In-order traversal of values
  virtual std::vector<Value> values_in_order() const = 0;

  // Get the height of the tree
  virtual int height() const = 0;

  // Get the number of nodes
  virtual size_t size() const = 0;

  // Clear the entire tree
  virtual void clear() = 0;

  // Check if the tree is empty
  virtual bool empty() const = 0;

  // Get the comparator being used
  virtual Compare comparator() const = 0;
};
