
#ifndef SEDP_EXERCISE3_MODULO_COUNTER_H
#define SEDP_EXERCISE3_MODULO_COUNTER_H

class ModuloCounter {
public:
    ModuloCounter(ModuloCounter& o) noexcept = default;
    ModuloCounter(int minValue, int maxValue) {
        min = minValue;
        max = maxValue;
        use_new_v();
    }
    ModuloCounter(int minValue, int maxValue, int initialValue) {
        min = minValue;
        max = maxValue;
        use_new_v();
        set_to(initialValue);
    }
    explicit ModuloCounter(std::tuple<int, int, int> stuff) {
        min = std::get<0>(stuff);
        max = std::get<1>(stuff);
        use_new_v();
        set_to(std::get<2>(stuff));
    }
    ModuloCounter& operator=(int smth) {
        set_to(smth);
        return *this;
    }
    void operator+(int stuff) {
        v += stuff;
    }
    void operator-(int stuff) {
        v -= stuff;
    }
    ModuloCounter operator--(int) {
        subtract(1);
        return *this;
    }
    ModuloCounter operator++() {
        add(1);
        return *this;
    }
    void operator+=(int smth) {
        add(smth);
    }
    void operator-=(int smth) {
        subtract(smth);
    }
    std::tuple<int, int, int> operator*(const ModuloCounter& other) {
        int range = std::abs(min - max);
        int rm = v * other.v;
        rm %= range;
        if (rm >= max) {
            rm -= range;
        }
        return std::make_tuple(min, max, rm);
    }
    [[nodiscard]] int value() const {
        return v;
    }
    [[nodiscard]] std::string gimme_some_chars() const {
        return std::to_string(v) + " in [" + std::to_string(min) + ", " + std::to_string(max)  + ")";
    }

private:
    int v{};
    int min;
    int max;

    void use_new_v() {
        if (min < 0 && max > 0) {
            v = 0;
        } else {
            v = min;
        }
    }

    void subtract(int smth) {
        int range = std::abs(min - max);
        int rm = v - smth;
        rm %= range;
        if (rm >= max) {
            rm -= range;
        }
        v = rm;
    }
    void add(int smth) {
        int range = std::abs(min - max);
        int rm = v + smth;
        rm %= range;
        if (rm >= max) {
            rm -= range;
        }
        v = rm;
    }
    void set_to(int smth) {
        add(smth);
    }

    void become(const ModuloCounter& counter) {
        min = counter.min;
        max = counter.max;
        v = counter.v;
    }
};


std::ostream& operator <<(std::ostream& stream, const ModuloCounter& counter) {
    return stream << counter.gimme_some_chars();
}

int operator*(int something, const ModuloCounter& stuff) {
    return something * stuff.value();
}

#endif //SEDP_EXERCISE3_MODULO_COUNTER_H
