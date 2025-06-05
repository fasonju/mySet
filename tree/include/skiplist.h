#pragma once

#include "tree.h"
#include <memory>
#include <random>
#include <vector>

template <typename T>
    requires std::totally_ordered<T>
class SkipList : AVLTree<T> {
    public:
        SkipList(int maxLevel = 20); //completely arbitrary value, log(1,000,000) =~ 20
        ~SkipList() override;

        bool insert(T&& value) override;
        bool remove(const T& value) override;
        T* search(const T& value) const override;
        T* max() const override;
        T* min() const override;
        bool contains(const T& value) const override;
        // [[nodiscard]] int height() const override;
        [[nodiscard]] size() const override;
        void clear() override;
        [[nodiscard]] bool empty() const override;

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
};