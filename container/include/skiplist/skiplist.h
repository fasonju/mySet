#pragma once

#include "container.h"
#include <random>
#include <vector>

constexpr int DEFAULT_MAX_LEVEL = 20;

template <typename T, typename Compare = std::less<T>> class SkipList {
  public:
    // this one (or the maxLevel) even necessary?
    explicit SkipList(int maxLevel = DEFAULT_MAX_LEVEL)
        : _maxLevel(maxLevel) {Node *x = new Node(0); _header = x;}; // completely arbitrary value,
                                  // log(1,000,000) =~ 20

    SkipList(const SkipList &) = delete;
    SkipList(SkipList &&) = delete;
    SkipList &operator=(const SkipList &) = delete;
    SkipList &operator=(SkipList &&) = delete;
    ~SkipList() = default;

    bool insert(T value);
    bool remove(const T &value);
    T *search(const T &value) const;
    T *max() const;
    T *min() const;
    bool contains(const T &value) const;
    [[nodiscard]] size_t size() const;
    void clear();
    [[nodiscard]] bool empty() const;

  private:
    struct Node {
        T value;
        std::vector<Node *> forward;

        Node(const T &val, int level) : value(val), forward(level, nullptr) {}
        explicit Node(int level) : forward(level, nullptr) {}
    };

    int randomLevel();
    Node *createNode(const T &value, int level);

    const int _maxLevel;
    int _currentLevel = 0;
    size_t _size = 0;
    Node *_header;
    mutable std::mt19937 _gen;
    mutable std::uniform_real_distribution<> _dist;
    Compare comp;
};

#include "skiplist/skiplist.hpp"

static_assert(Dontainer<SkipList<int>, int>);
