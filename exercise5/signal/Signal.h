
#pragma once

#include <vector>
#include <functional>

template<typename ...T>
class Signal {
public:

    Signal() = default;

    void connect(const std::function<void(T...)> &lambda) {
        functions.push_back(lambda);
    }

    template<typename K>
    void connect(K k, const std::function<void(const K, T...)> &lambda) {
        functions.push_back([k, lambda](T... t) {
            lambda(k, t...);
        });
    }

    void emit(T... t) {
        for (auto fun : functions) {
            fun(t...);
        }
    }

private:
    std::vector<std::function<void(T...)>> functions;
};