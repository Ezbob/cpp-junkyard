#ifndef HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8
#define HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8

#include <cmath>
#include <iostream>
#include <ostream>
#include <initializer_list>

template<std::size_t Dim, typename T>
class Vec {
    T value[Dim];

public:
    std::size_t dimension = Dim;

    Vec() = default;

    explicit Vec(const std::initializer_list<T> &&args) {
        std::size_t i = 0;
        for (const T arg : args) {
            value[i++] = arg;
        }
    }

    static Vec<Dim, T> initialized(T initializeValue) {
        Vec<Dim, T> res;

        for (int i = 0; i < Dim; ++i) {
            res.value[i] = initializeValue;
        }

        return res; 
    }

    constexpr static Vec<Dim, T> zero() {
        return Vec<Dim, T>::initialized(0);
    }

    constexpr static Vec<Dim, T> one() {
        return Vec<Dim, T>::initialized(1);
    }

    T operator[] (int i) const {
        return value[i];
    }

    Vec<Dim, T> add(const Vec<Dim, T> &other) const {
        Vec<Dim, T> result;
        for (int i = 0; i < Dim; ++i) {
            result.value[i] = value[i] + other[i];
        }
        return result;
    }

    Vec<Dim, T> sub(const Vec<Dim, T> &other) const {
        Vec<Dim, T> result;
        for (int i = 0; i < Dim; ++i) {
            result.value[i] = value[i] + other[i];
        }
        return result;
    }

    Vec<Dim, T> mul(const T &other) const {
        Vec<Dim, T> result;
        for (int i = 0; i < Dim; ++i) {
            result.value[i] = value[i] * other;
        }
        return result;
    }

    Vec<Dim, T> div(const T &other) const {
        Vec<Dim, T> result;
        for (int i = 0; i < Dim; ++i) {
            result.value[i] = value[i] / other;
        }
        return result;
    }

    Vec<Dim, T> operator +(const Vec<Dim, T> &other) const {
        return add(other);
    }

    Vec<Dim, T> operator -(const Vec<Dim, T> &other) const {
        return add(other);
    }

    Vec<Dim, T> operator *(const T &other) const {
        return mul(other);
    }

    Vec<Dim, T> operator /(const T &other) const {
        return div(other);
    }

    T dot(Vec<Dim, T> &other) const {
        T result = 0;

        for (std::size_t i = 0; i < Dim; ++i) {
            result += value[i] * other.value[i];
        }

        return result;
    }

    T mag() const {
        T result = 0;

        for (std::size_t i = 0; i < Dim; ++i) {
            result += value[i] * value[i];
        }

        return std::sqrt(result);
    }

    Vec<Dim, T> norm() const {
        return div(mag());
    }

    T *begin() {
        return &value[0];
    }

    T *end() {
        return &value[Dim];
    }

    template<std::size_t D, typename U>
    friend std::ostream& operator <<(std::ostream&, const Vec<D, U>&);
};

template<std::size_t D, typename U>
std::ostream& operator <<(std::ostream& os, const Vec<D, U> &vec) {
    os << "(";
    if (vec.dimension > 0) {
        os << vec[0];
        for (std::size_t i = 1; i < vec.dimension; ++i) 
            os << ", " << vec[i];
    }
    os << ")";
    return os;
}

template<typename T>
using Vec2 = Vec<2, T>;

using VecR2 = Vec<2, double>;

template<typename T>
using Vec3 = Vec<3, T>;

using VecR3 = Vec<3, double>;


#endif
