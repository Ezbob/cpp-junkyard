#include <iostream>


template<typename T>
struct is_int {
    constexpr static bool value = false;
};

template<>
struct is_int<int> {
    constexpr static bool value = true;
};

template<typename T>
void print_if_int() {
    if (is_int<T>::value) {
        std::cout << "is int" << std::endl;
    } else {
        std::cout << "not is int" << std::endl;
    }
}

int main() {
    auto a = 32;
    constexpr auto b = 2.3;

    print_if_int<decltype(a)>();
    print_if_int<decltype(b)>();

    return 0;
}