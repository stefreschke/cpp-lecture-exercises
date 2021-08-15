
#pragma once

#include <type_traits>

class Variant {
public:
    template <typename T> explicit Variant(T stuff) {
        this->stuff = static_cast<void*>(&stuff);
        this->tname = typeid(T).name();
    }

    explicit Variant() = default;

    template <typename T> bool hasType() {
        return typeid(T).name() == this->tname;
    }

    template <typename T> T get() {
        if (hasType<T>())
            return *static_cast<T*>(stuff);
        throw std::logic_error("IMPOSSIBLE");
    }
private:
    void* stuff{};
    std::string tname;
};
