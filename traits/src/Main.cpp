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

/*
template<typename...>
using try_to_instantiate = void;

template<typename, typename = void>
struct is_incrementable : std::false_type {};

template<typename T>
struct is_incrementable<T,
    std::void_t<decltype(++std::declval<T &>())> 
    > : std::true_type {};

template<typename T>
struct is_incrementable<T, 
    try_to_instantiate<decltype(++std::declval<T &>())> 
    > : std::true_type {};
*/

template<template<typename...> class Expression, typename Attempt, typename... Ts>
struct has_expression_impl : std::false_type {};
    // if any specialization does not get instantiated then we defaults to this template
    // it inheriates from false_type which like the true_type has the "value" bool member (set to false)

template<template<typename...> class Expression, typename... Ts>
struct has_expression_impl<Expression, std::void_t<Expression<Ts...>>, Ts...> : std::true_type {};
    // if the std::void_t can be expanded / substituated then this specialization will take priority
    // the true_type makes the "value" bool member available and set to true

template<template<typename...> class Expression, typename... Ts>
constexpr bool has_expression = has_expression_impl<Expression, void, Ts...>::value;
    // the void here implements the template instantiation 


// here we implement the is'ers 

template<typename T>
using increment_expression = decltype(++std::declval<T&>());

template<typename T>
constexpr bool is_incrementable = has_expression<increment_expression, T>;


template<typename T, typename U>
using assign_expression = decltype(std::declval<T&>() = std::declval<U &>());

template<typename T, typename U>
constexpr bool is_assignable = has_expression<assign_expression, T, U>;


class Bull {
    int a = 0;
public:
    void operator ++() {
        ++a;
    }
};


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

    std::cout << is_incrementable<decltype(a)> << std::endl;

    Bull bull;

    std::cout << is_incrementable<decltype(bull)> << std::endl;

    static_assert(is_assignable<int, double>, "Ooof");
    static_assert(is_assignable<int, long>, "Ooof");

    return 0;
}