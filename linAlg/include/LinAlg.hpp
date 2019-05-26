#ifndef HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8
#define HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8

#include <cmath>
#include <iostream>
#include <ostream>
#include <array>

namespace LinAlg {

    template<std::size_t Dim, typename T>
    class Vec {
        T _data[Dim] = {0};

    public:
        constexpr static std::size_t dimension = Dim;

        constexpr Vec() noexcept {};

        constexpr explicit Vec(const T(&args)[Dim]) noexcept {
            for (std::size_t i = 0; i < Dim; ++i) {
                _data[i] = args[i];
            }
        }

        constexpr static Vec<Dim, T> initWith(const T &initializeValue) noexcept {
            Vec<Dim, T> res;

            for (std::size_t i = 0; i < Dim; ++i) {
                res._data[i] = initializeValue;
            }

            return res; 
        }

        constexpr static Vec<Dim, T> zeroes() noexcept {
            return Vec<Dim, T>::initWith(0);
        }

        constexpr static Vec<Dim, T> ones() noexcept {
            return Vec<Dim, T>::initWith(1);
        }

        constexpr T operator[](std::size_t i) const noexcept {
            return _data[i];
        }

        constexpr Vec<Dim, T> add(const Vec<Dim, T> &other) const noexcept {
            Vec<Dim, T> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + other._data[i];
            }
            return result;
        }

        constexpr Vec<Dim, T> add(const T &scalar) const noexcept {
            Vec<Dim, T> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + scalar;
            }
            return result;
        }

        constexpr Vec<Dim, T> sub(const T &scalar) const noexcept {
            Vec<Dim, T> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] - scalar;
            }
            return result;
        }

        constexpr Vec<Dim, T> sub(const Vec<Dim, T> &other) const noexcept {
            Vec<Dim, T> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + other._data[i];
            }
            return result;
        }

        constexpr Vec<Dim, T> mul(const T &scalar) const noexcept {
            Vec<Dim, T> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] * scalar;
            }
            return result;
        }

        constexpr Vec<Dim, T> mul(const Vec<Dim, T> &other) const noexcept {
            Vec<Dim, T> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] * other._data[i];
            }
            return result;
        }

        constexpr Vec<Dim, T> div(const T &scalar) const noexcept {
            Vec<Dim, T> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] / scalar;
            }
            return result;
        }

        constexpr Vec<Dim, T> div(const Vec<Dim, T> &other) const noexcept {
            Vec<Dim, T> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] / other._data[i];
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
                result += _data[i] * other._data[i];
            }

            return result;
        }

        constexpr T mag() const noexcept {
            T result = 0;

            for (std::size_t i = 0; i < Dim; ++i) {
                result += _data[i] * _data[i];
            }

            return std::sqrt(result);
        }

        constexpr Vec<Dim, T> norm() const noexcept {
            return div(mag());
        }

        constexpr T *begin() const noexcept {
            return &_data[0];
        }

        constexpr T *end() const noexcept {
            return &_data[Dim];
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

    // ---
    // Easy aliases
    // ---

    template<std::size_t Dim>
    using VecR = Vec<Dim, double>;

    template<typename T>
    using Vec2 = Vec<2, T>;

    using VecR2 = Vec<2, double>;

    template<typename T>
    using Vec3 = Vec<3, T>;

    using VecR3 = Vec<3, double>;

}

#endif
