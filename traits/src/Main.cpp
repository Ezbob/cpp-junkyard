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
struct is_pointer {
    constexpr static bool value = false;
};

template<typename T>
struct is_pointer<T *> {
    constexpr static bool value = true;
};

template<typename T>
constexpr void print_if_int(const T &value) {
    if (is_int<T>::value) {
        std::cout << "is int" << std::endl;
    } else {
        std::cout << "not is int" << std::endl;
    }
}

/* super cool algorithm is not implemented so there is a default one */
template< bool b >
struct algorithm_chooser {
    template< typename T >
    static void implementation(T &object) {
        object += 10;
    }
};


/* super cool algorithm is implemented here */
template<>
struct algorithm_chooser<true> {
    template< typename T >
    static void implementation(T &object) {
        if (is_int<T>::value) {
            object += 15;
        }
    }
};

/* support trait - makes certain types allowed
 * you can also mark user defined types (classes)
 */
template<typename T>
struct supports_super_cool_algorithm {
    constexpr static bool value = false;
};

template<>
struct supports_super_cool_algorithm<int> {
    constexpr static bool value = true;
};

template<>
struct supports_super_cool_algorithm<float> {
    constexpr static bool value = true;
};

/*
 * the applier
 */
template<typename T>
void algorithm(T &obj) {
    algorithm_chooser<supports_super_cool_algorithm<T>::value>::implementation(obj);
}

int main() {
    constexpr auto a = 32;
    const auto b = 2.3;
    double c = 2.10l;

    print_if_int(a);
    print_if_int(b);

    auto fun = 10;
    algorithm(fun);
    algorithm(c);

    std::cout << a << "--" << c << std::endl;

    return 0;
}