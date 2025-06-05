#pragma once

#include <concepts>
#include <cstddef>

template <typename C, typename T>
concept Dontainer = requires(C container, T value, const T &const_value) {
    // modifiers
    { container.insert(value) } -> std::same_as<bool>;
    { container.remove(const_value) } -> std::same_as<bool>;
    { container.clear() } -> std::same_as<void>;

    // access
    { container.search(const_value) } -> std::same_as<T *>;
    { container.max() } -> std::same_as<T *>;
    { container.min() } -> std::same_as<T *>;

    // info
    { container.contains(const_value) } -> std::same_as<bool>;
    { container.size() } -> std::same_as<std::size_t>;
    { container.empty() } -> std::same_as<bool>;
};
