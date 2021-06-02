
#include <iostream>
#include <tuple>
#include "modulo_counter.h"

int main(int argc, char * argv[])
{
    ModuloCounter m1 {0, 10};
    std::cout << m1 << std::endl;

    m1 += 23;
    std::cout << m1 << std::endl;

    auto m2 = ++m1;;
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    auto m3 (m2--);
    std::cout << m2 << std::endl;
    std::cout << m3 << std::endl;

    ModuloCounter m4 {-7, 18};
    std::cout << m4 << std::endl;

    m4 = 267;
    std::cout << m4 << std::endl;

    ModuloCounter m5 {m4 * m3};
    std::cout << m5 << std::endl;

    m5 = m2;
    std::cout << m5 << std::endl;
    // set m5 to m2

    ModuloCounter m6 {-11, -3, m5.value()};
    std::cout << m6 << std::endl;

    int i1 {m6.value()};
    std::cout << i1 << std::endl;

    m6 -= 7;
    auto m7{m6};
    std::cout << m7 << std::endl;

    int i2 {5 * m7};
    std::cout << i2 << std::endl;
}
