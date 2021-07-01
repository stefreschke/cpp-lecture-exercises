
#pragma once

#include <functional>

/*
 * Taken from: https://stackoverflow.com/a/37378929
 */
template <class C, class V>
auto append(C& container, V&& value, int)
-> decltype(container.push_back(std::forward<V>(value)), void())
{
    container.push_back(std::forward<V>(value));
}

template <class C, class V>
void append(C& container, V&& value, ...)
{
    container.insert(std::forward<V>(value));
}

template <class C, class V>
void AddToContainer(C& container, V&& value) {
    append(container, std::forward<V>(value), 0);
}

/*
 * own templated #collect
 */
template <class C1, class C2>
C1 collect(const C2& collection, const std::function<typename C1::value_type(typename C2::value_type)>& lambda) {
    C1 result{};
    for (auto t2 : collection) {
        auto t1 = lambda(t2);
        AddToContainer(result, t1);
    }
    return result;
}

