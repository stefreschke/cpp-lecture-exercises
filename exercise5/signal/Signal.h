
#pragma once

#include <vector>
#include <functional>

template <typename ...T>
class Signal {
public:

    Signal() = default;

    void connect(const std::function<void(T...)>& smth) {
        functions.push_back(smth);
    }

    void emit(T... t) {
        for (auto fun : functions) {
            fun(t...);
        }
    }

private:
    std::vector<std::function<void(T...)>> functions;
};