#pragma once

#include "skiplist/skiplist.h"

constexpr float LEVEL_UP_CHANCE = 0.5;

// Insert a value into the skiplist
// return true if successfully inserted, false otherwise
template <typename T, typename Compare>
bool SkipList<T, Compare>::insert(T value) {
    // to keep track of pointers from nodes to update
    std::vector<Node *> update(_maxLevel, nullptr);
    Node *current = _header;

    // start at highest express lane, go down a level when next node is
    // higher than node we are looking for
    for (int level = _currentLevel - 1; level >= 0; --level) {
        bool lessThan = comp(current->forward[level]->value, value);
        while (current->forward[level] && lessThan) {
            current = current->forward[level];
        }
    }

    current = current->forward[0];

    // if node with value already exists, dont insert
    bool equal = !comp(value, current->value) && !comp(current->value, value);
    if (current && equal) {
        return false;
    }

    // get level of node for express lanes
    int nodeLevel = randomLevel();

    // if not enough express lanes exist for the generated level, create them
    if (nodeLevel > _currentLevel) {
        for (int i = _currentLevel; i < nodeLevel; ++i) {
            update[i] = _header;
        }
        _currentLevel = nodeLevel;
    }

    Node *newNode = createNode(value, nodeLevel);

    for (int i = 0; i < nodeLevel; ++i) {
        // set outgoing pointers to next point in lane
        newNode->forward[i] = update[i]->forward[i];

        // set incoming pointers from the memorized update list
        update[i]->forward[i] = newNode;
    }

    ++_size;
    return true;
}

// Remove a value from the skiplist
// return true if successfully removed, false otherwise
template <typename T, typename Compare>
bool SkipList<T, Compare>::remove(const T &value) {
    std::vector<Node *> update(_maxLevel, nullptr);
    Node *current = _header;

    // start at highest express lane, go down a level when next node is
    // higher than node we are looking for
    for (int level = _currentLevel - 1; level >= 0; --level) {
        bool lessThan = comp(current->forward[level]->value, value);
        while (current->forward[level] && lessThan) {
            current = current->forward[level];
        }
    }

    current = current->forward[0];

    // if value doesnt exist, return false
    if ((current == nullptr) || comp(value, current->value) ||
        comp(current->value, value)) {
        return false;
    }

    // update forward pointers to point at next item on each express lane
    for (int i = 0; i < _currentLevel; ++i) {
        // check if there are no more pointers at this level or further
        if (update[i]->forward[i] != current) {
            break;
        }
        update[i]->forward[i] = current->forward[i];
    }

    delete current;
    --_size;

    // update current level if necessary (deleted a node of the highest express
    // lane)
    while (_currentLevel > 1 &&
           _header->forward[_currentLevel - 1] == nullptr) {
        --_currentLevel;
    }

    return true;
}

// Search the skiplist for a value
// return the node if the value exists, else return a nullpointer
template <typename T, typename Compare>
T *SkipList<T, Compare>::search(const T &value) const {
    Node *current = _header;

    // start at highest express lane, go down a level when next node is
    // higher than node we are looking for
    for (int level = _currentLevel - 1; level >= 0; --level) {
        bool lessThan = comp(current->forward[level]->value, value);
        while (current->forward[level] && lessThan) {
            current = current->forward[level];
        }
    }

    current = current->forward[0];

    // Check if the found node equals the value
    bool equal = !comp(value, current->value) && !comp(current->value, value);
    if (current && equal) {
        return &current->value;
    }

    return nullptr;
}

// go all the way to the lowest layer of skiplist,
// then run through until you reach a node that has no pointers out
// return value of last node
template <typename T, typename Compare> T *SkipList<T, Compare>::max() const {
    Node *x = _header;
    // Traverse as far as possible on level 0
    while (x->forward[0] != nullptr) {
        x = x->forward[0];
    }

    // If list is empty, x == _header, and x->forward[0] == nullptr
    return (x == _header) ? nullptr : &x->value;
}

// return the element after the dummy header
template <typename T, typename Compare> T *SkipList<T, Compare>::min() const {
    Node *x = _header->forward[0];
    return x ? &x->value : nullptr;
}

// Look if a value exists in the skiplist
// return true if it exists, else return false
template <typename T, typename Compare>
bool SkipList<T, Compare>::contains(const T &value) const {
    Node *current = _header;

    // start at highest express lane, go down a level when next node is
    // higher than node we are looking for
    for (int level = _currentLevel - 1; level >= 0; --level) {
        bool lessThan = comp(current->forward[level]->value, value);
        while (current->forward[level] && lessThan) {
            current = current->forward[level];
        }
    }

    // next node is the one we are looking for
    current = current->forward[0];

    bool equal = !comp(value, current->value) && !comp(current->value, value);
    return current && equal;
}

// Clear the whole skiplist of its nodes and reset the headers' pointers
template <typename T, typename Compare> void SkipList<T, Compare>::clear() {
    Node *current = _header->forward[0];

    // delete all nodes by traversing lvl 0
    while (current != nullptr) {
        Node *next = current->forward[0];
        delete current;
        current = next;
    }

    // reset header pointers
    for (auto &ptr : _header->forward) {
        ptr = nullptr;
    }

    _size = 0;
    _currentLevel = 1;
}

// check if there are elements in the skiplist (besides header)
template <typename T, typename Compare>
bool SkipList<T, Compare>::empty() const {
    return _size == 0; // no need for generic compare function
}

// return the number of elements in the skiplist
template <typename T, typename Compare>
size_t SkipList<T, Compare>::size() const {
    return _size;
}

// flip a coin, if heads, increment by one and flip again
// if tails, stop and return
template <typename T, typename Compare>
int SkipList<T, Compare>::randomLevel() {
    int level = 1;
    while (_dist(_gen) < LEVEL_UP_CHANCE && level < _maxLevel) {
        ++level;
    }
    return level;
}

// create a node with a value and its level (how many express lanes it covers)
template <typename T, typename Compare>
typename SkipList<T, Compare>::Node *
SkipList<T, Compare>::createNode(const T &value, int level) {
    return new Node(value, level);
}
