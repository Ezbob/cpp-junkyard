#ifndef HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8
#define HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8

#include <cmath>
#include <iostream>
#include <ostream>
#include <array>
#include <initializer_list>

template<std::size_t Dim, typename T>
class Vec {
    T value[Dim] = {0};

public:
    const std::size_t dimension = Dim;

    constexpr Vec() noexcept {};

    constexpr explicit Vec(const std::initializer_list<T> &&args) noexcept {
        std::size_t i = 0;
        for (const T arg : args) {
            value[i++] = arg;
        }
    }

    constexpr explicit Vec(const T *args) noexcept {
        for (std::size_t i = 0; i < Dim; ++i) {
            value[i] = args[i];
        }
    }

    constexpr static Vec<Dim, T> initialized(const T &&initializeValue) noexcept {
        Vec<Dim, T> res;

        for (std::size_t i = 0; i < Dim; ++i) {
            res.value[i] = initializeValue;
        }

        return res; 
    }

    constexpr static Vec<Dim, T> zero() noexcept {
        return Vec<Dim, T>::initialized(0);
    }

    constexpr static Vec<Dim, T> one() noexcept {
        return Vec<Dim, T>::initialized(1);
    }

    constexpr T operator[] (std::size_t i) const noexcept {
        return value[i];
    }

    constexpr Vec<Dim, T> add(const Vec<Dim, T> &other) const noexcept {
        Vec<Dim, T> result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.value[i] = value[i] + other[i];
        }
        return result;
    }

    constexpr Vec<Dim, T> add(const T &scalar) const noexcept {
        Vec<Dim, T> result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.value[i] = value[i] + scalar;
        }
        return result;
    }

    constexpr Vec<Dim, T> sub(const T &scalar) const noexcept {
        Vec<Dim, T> result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.value[i] = value[i] - scalar;
        }
        return result;
    }

    constexpr Vec<Dim, T> sub(const Vec<Dim, T> &other) const noexcept {
        Vec<Dim, T> result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.value[i] = value[i] + other[i];
        }
        return result;
    }

    constexpr Vec<Dim, T> mul(const T &scalar) const noexcept {
        Vec<Dim, T> result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.value[i] = value[i] * scalar;
        }
        return result;
    }

    constexpr Vec<Dim, T> mul(const Vec<Dim, T> &other) const noexcept {
        Vec<Dim, T> result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.value[i] = value[i] * other[i];
        }
        return result;
    }

    constexpr Vec<Dim, T> div(const T &scalar) const noexcept {
        Vec<Dim, T> result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.value[i] = value[i] / scalar;
        }
        return result;
    }

    constexpr Vec<Dim, T> div(const Vec<Dim, T> &other) const noexcept {
        Vec<Dim, T> result;
        for (std::size_t i = 0; i < Dim; ++i) {
            result.value[i] = value[i] / other[i];
        }
        return result;
    }

    constexpr Vec<Dim, T> operator +(const Vec<Dim, T> &other) const noexcept {
        return add(other);
    }

    constexpr Vec<Dim, T> operator -(const Vec<Dim, T> &other) const noexcept {
        return add(other);
    }

    constexpr Vec<Dim, T> operator *(const T &other) const noexcept {
        return mul(other);
    }

    constexpr Vec<Dim, T> operator /(const T &other) const noexcept {
        return div(other);
    }

    constexpr T dot(Vec<Dim, T> &other) const noexcept {
        T result = 0;

        for (std::size_t i = 0; i < Dim; ++i) {
            result += value[i] * other.value[i];
        }

        return result;
    }

    constexpr T mag() const noexcept {
        T result = 0;

        for (std::size_t i = 0; i < Dim; ++i) {
            result += value[i] * value[i];
        }

        return std::sqrt(result);
    }

    constexpr Vec<Dim, T> norm() const noexcept {
        return div(mag());
    }

    constexpr T *begin() const noexcept {
        return &value[0];
    }

    constexpr T *end() const noexcept {
        return &value[Dim];
    }

    template<std::size_t D, typename U>
    friend constexpr std::ostream& operator <<(std::ostream&, const Vec<D, U>&) noexcept;
};

template<std::size_t D, typename U>
constexpr std::ostream& operator <<(std::ostream& os, const Vec<D, U> &vec) noexcept {
    os << "(";
    if (vec.dimension > 0) {
        os << vec[0];
        for (std::size_t i = 1; i < vec.dimension; ++i) 
            os << ", " << vec[i];
    }
    os << ")";
    return os;
}

template<std::size_t Dim>
using VecR = Vec<Dim, double>;

template<typename T>
using Vec2 = Vec<2, T>;

using VecR2 = Vec<2, double>;

template<typename T>
using Vec3 = Vec<3, T>;

using VecR3 = Vec<3, double>;


#endif
