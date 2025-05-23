#pragma once

#include <optional>
#include <vector>

template <typename Key, typename Value> class ITree {
public:
  virtual ~ITree() = default;

  // Insert a key-value pair into the tree
  virtual void insert(const Key &key, const Value &value) = 0;

  // Remove a key from the tree
  virtual bool remove(const Key &key) = 0;

  // Search for a key and return the associated value (if found)
  virtual std::optional<Value> search(const Key &key) const = 0;

  // Check if the tree contains a specific key
  virtual bool contains(const Key &key) const = 0;

  // In-order traversal of keys
  virtual std::vector<Key> keys_in_order() const = 0;

  // Get the height of the tree
  virtual int height() const = 0;

  // Get the number of nodes
  virtual size_t size() const = 0;

  // Clear the entire tree
  virtual void clear() = 0;

  // Check if the tree is empty
  virtual bool empty() const = 0;
};
