
#include <iostream>
#include <tuple>
// include appropriate header file

struct ModuloMultiplicationResult {
public:

};

class ModuloCounter {
public:
    [[nodiscard]] ModuloCounter create_copy() const {
        ModuloCounter copy{min, max};
        copy.add(v);
        return copy;
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
    void decrement() {
        subtract(1);
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
    [[nodiscard]] std::string gimme_some_chars() const {
        return std::to_string(v) + " in [" + std::to_string(min) + ", " + std::to_string(max)  + ")";
    }
    void operator+(int stuff) {
        v += stuff;
    }
    ModuloCounter(ModuloCounter& o) noexcept : min(o.min), max(o.max), v(o.v) {};
    ModuloCounter(ModuloCounter&& o) noexcept : min(o.min), max(o.max), v(o.v) {};
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
    ModuloCounter(std::tuple<int, int, int> stuff) {
        min = std::get<0>(stuff);
        max = std::get<1>(stuff);
        use_new_v();
        set_to(std::get<2>(stuff));
    }

    std::tuple<int, int, int> multiplyWith(ModuloCounter counter) {
        int range = std::abs(min - max);
        int rm = v * counter.v;
        rm %= range;
        if (rm >= max) {
            rm -= range;
        }
        return std::make_tuple(min, max, rm);
    }

    [[nodiscard]] int value() const {
        return v;
    }

    void become(ModuloCounter counter) {
        min = counter.min;
        max = counter.max;
        v = counter.v;
    }

private:
    int v;
    int min;
    int max;

    void use_new_v() {
        if (min < 0 && max > 0) {
            v = 0;
        } else {
            v = min;
        }
    }
};


std::ostream& operator <<(std::ostream& stream, const ModuloCounter& counter) {
    return stream << counter.gimme_some_chars();
}

int operator*(int something, ModuloCounter stuff) {
    return something * stuff.value();
}

int main(int argc, char * argv[])
{
    ModuloCounter m1 {0, 10};
    std::cout << m1 << std::endl;

    m1.add(23);
    std::cout << m1 << std::endl;

    m1.add(1);
    auto m2 = m1.create_copy();
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    // decrement m2 and create ModuloCounter m3 with the old value
    auto m3 = m2.create_copy();
    m2.decrement();
    std::cout << m2 << std::endl;
    std::cout << m3 << std::endl;

    ModuloCounter m4 {-7, 18};
    std::cout << m4 << std::endl;

    m4.set_to(267);
    std::cout << m4 << std::endl;

    // create ModuloCounter m5 with the result of multiplying m4 and m3
    ModuloCounter m5 {m4.multiplyWith(m3)};
    std::cout << m5 << std::endl;

    m5.become(m2);
    std::cout << m5 << std::endl;
    // set m5 to m2

    ModuloCounter m6 {-11, -3, m5.value()};
    std::cout << m6 << std::endl;
    // create ModuloCounter m6 with the interval [-11, -3) and initial value of m5

    int i1 {m6.value()};
    std::cout << i1 << std::endl;
    // create int i1 with the value of m6

    // create ModuloCounter m7 with the result of subtracting 7 from m6
    m6.subtract(7);
    auto m7{m6};
    std::cout << m7 << std::endl;

    // create int i2 with the value of multiplying 5 with m7
    int i2 {5 * m7};
    std::cout << i2 << std::endl;
    // print i2
}
