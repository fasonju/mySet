#pragma once

#include <memory>
#include <random>
#include <vector>
#include "container.h"

template <typename T, typename Compare = std::less<T>>
class SkipList {
    public:
        //this one (or the maxLevel) even necessary?
        SkipList(int maxLevel = 20); //completely arbitrary value, log(1,000,000) =~ 20

        ~SkipList();

        bool insert(T value);
        bool remove(const T& value);
        T* search(const T& value) const;
        T* max() const;
        T* min() const;
        bool contains(const T& value) const;
        [[nodiscard]] size_t size() const;
        void clear();
        [[nodiscard]] bool empty() const;

    private:
        struct Node {
            T value;
            std::vector<Node*> forward;

            Node(const T& val, int level) : value(val), forward(level, nullptr) {}
        };

        int randomLevel();
        Node* createNode(const T& value, int level);

        const int _maxLevel;
        int _currentLevel;
        size_t _size;
        Node* _header;
        mutable std::mt19937 _gen;
        mutable std::uniform_real_distribution<> _dist;
        Compare comp;
};

#include "skiplist.hpp"

static_assert(Dontainer<SkipList<int>, int>);
