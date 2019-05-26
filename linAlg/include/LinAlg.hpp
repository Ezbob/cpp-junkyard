#ifndef HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8
#define HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8

#include <cmath>
#include <ostream>

namespace LinAlg {

    template<typename T, std::size_t Dim>
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

        constexpr static Vec<T, Dim> initWith(const T &initializeValue) noexcept {
            Vec<T, Dim> res;

            for (std::size_t i = 0; i < Dim; ++i) {
                res._data[i] = initializeValue;
            }

            return res; 
        }

        constexpr static Vec<T, Dim> zeroes() noexcept {
            return Vec<T, Dim>::initWith(0);
        }

        constexpr static Vec<T, Dim> ones() noexcept {
            return Vec<T, Dim>::initWith(1);
        }

        constexpr T operator[](std::size_t i) const noexcept {
            return _data[i];
        }

        constexpr Vec<T, Dim> add(const Vec<T, Dim> &other) const noexcept {
            Vec<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + other._data[i];
            }
            return result;
        }

        constexpr Vec<T, Dim> add(const T &scalar) const noexcept {
            Vec<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + scalar;
            }
            return result;
        }

        constexpr Vec<T, Dim> sub(const T &scalar) const noexcept {
            Vec<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] - scalar;
            }
            return result;
        }

        constexpr Vec<T, Dim> sub(const Vec<T, Dim> &other) const noexcept {
            Vec<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + other._data[i];
            }
            return result;
        }

        constexpr Vec<T, Dim> mul(const T &scalar) const noexcept {
            Vec<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] * scalar;
            }
            return result;
        }

        constexpr Vec<T, Dim> mul(const Vec<T, Dim> &other) const noexcept {
            Vec<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] * other._data[i];
            }
            return result;
        }

        constexpr Vec<T, Dim> div(const T &scalar) const noexcept {
            Vec<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] / scalar;
            }
            return result;
        }

        constexpr Vec<T, Dim> div(const Vec<T, Dim> &other) const noexcept {
            Vec<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] / other._data[i];
            }
            return result;
        }

        constexpr Vec<T, Dim> operator +(const Vec<T, Dim> &other) const noexcept {
            return add(other);
        }

        constexpr Vec<T, Dim> operator -(const Vec<T, Dim> &other) const noexcept {
            return add(other);
        }

        constexpr Vec<T, Dim> operator *(const T &other) const noexcept {
            return mul(other);
        }

        constexpr Vec<T, Dim> operator /(const T &other) const noexcept {
            return div(other);
        }

        constexpr T dot(Vec<T, Dim> &other) const noexcept {
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

        constexpr Vec<T, Dim> norm() const noexcept {
            return div(mag());
        }

        constexpr T *begin() const noexcept {
            return &_data[0];
        }

        constexpr T *end() const noexcept {
            return &_data[Dim];
        }

        template<typename U, std::size_t D>
        friend constexpr std::ostream& operator <<(std::ostream&, const Vec<U, D>&) noexcept;
    };

    template<typename U, std::size_t D>
    constexpr std::ostream& operator <<(std::ostream& os, const Vec<U, D> &vec) noexcept {
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
    using VecR = Vec<double, Dim>;

    template<typename T>
    using Vec2 = Vec<T, 2>;

    using VecR2 = Vec<double, 2>;

    template<typename T>
    using Vec3 = Vec<T, 3>;

    using VecR3 = Vec<double, 3>;

}

#endif
