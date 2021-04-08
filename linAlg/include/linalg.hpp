#ifndef HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8_linalg
#define HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8_linalg

#include <cmath>
#include <iostream>
#include <type_traits>

namespace LinAlg {

    template<typename T, std::size_t Dim>
    using VectorEqualsComparator_t = bool(const T(&)[Dim], const T(&)[Dim]) noexcept;

    template<typename T, std::size_t Dim>
    constexpr bool DefaultVectorEqualsComparator(const T(& vec1)[Dim], const T(& vec2)[Dim]) noexcept {
        for (size_t i = 0; i < Dim; ++i)
            if (vec1[i] != vec2[i])
                return false;
        return true;
    }

    template<typename T, std::size_t Dim, VectorEqualsComparator_t<T, Dim> EqualsComparator = DefaultVectorEqualsComparator<T, Dim>, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
    struct VecBase {
        T _data[Dim] = {0};

        constexpr VecBase() noexcept = default;

        constexpr explicit VecBase(const T(&args)[Dim]) noexcept {
            for (std::size_t i = 0; i < Dim; ++i) {
                _data[i] = args[i];
            }
        }

        constexpr static VecBase<T, Dim> initWith(const T &initializeValue) noexcept {
            VecBase<T, Dim> res;

            for (std::size_t i = 0; i < Dim; ++i) {
                res._data[i] = initializeValue;
            }

            return res; 
        }

        constexpr static VecBase<T, Dim> zeroes() noexcept {
            return VecBase<T, Dim>{};
        }

        constexpr static VecBase<T, Dim> ones() noexcept {
            return VecBase<T, Dim>::initWith(1);
        }

        constexpr T operator[](std::size_t i) const noexcept {
            return _data[i];
        }

        constexpr VecBase<T, Dim> operator +(const VecBase<T, Dim> &other) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + other._data[i];
            }
            return result;
        }

        constexpr VecBase<T, Dim> operator +(const T &scalar) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + scalar;
            }
            return result;
        }

        constexpr VecBase<T, Dim> operator -(const VecBase<T, Dim> &other) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] - other._data[i];
            }
            return result;
        }

        constexpr VecBase<T, Dim> operator -(const T &scalar) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] - scalar;
            }
            return result;
        }

        constexpr VecBase<T, Dim> operator *(const T &scalar) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] * scalar;
            }
            return result;
        }

        constexpr VecBase<T, Dim> operator *(const VecBase<T, Dim> &other) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] * other._data[i];
            }
            return result;
        }

        constexpr VecBase<T, Dim> operator /(const T &scalar) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] / scalar;
            }
            return result;
        }

        constexpr VecBase<T, Dim> operator /(const VecBase<T, Dim> &other) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] / other._data[i];
            }
            return result;
        }

        constexpr bool operator ==(const VecBase<T, Dim> &other) const noexcept {
            return EqualsComparator(_data, other._data);
        }

        template<std::size_t A>
        constexpr bool operator ==(const VecBase<T, A> &other) const noexcept {
            return false;
        }

        constexpr bool operator !=(const VecBase<T, Dim> &other) const noexcept {
            return !EqualsComparator(_data, other._data);
        }

        template<std::size_t A>
        constexpr bool operator !=(const VecBase<T, A> &other) const noexcept {
            return true;
        }

        constexpr T dot(VecBase<T, Dim> &other) const noexcept {
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

        constexpr VecBase<T, Dim> norm() const noexcept {
            return div(mag());
        }

        constexpr const T *begin() const noexcept {
            return _data;
        }

        constexpr const T *end() const noexcept {
            return _data + Dim;
        }

        constexpr std::size_t len() noexcept {
            return Dim;
        }

        template<typename U = T>
        constexpr typename std::enable_if_t<Dim >= 1, U> x() const noexcept {
            return _data[0];
        }

        template<typename U = T>
        constexpr typename std::enable_if_t<Dim >= 2, U> y() const noexcept {
            return _data[1];
        }

        template<typename U = T>
        constexpr typename std::enable_if_t<Dim >= 3, U> z() const noexcept {
            return _data[2];
        }

        template<typename U = T>
        constexpr typename std::enable_if_t<Dim >= 4, U> w() const noexcept {
            return _data[3];
        }

        template<typename U = T>
        constexpr typename std::enable_if_t<Dim == 2, U> cross(const VecBase<U, Dim> &other) const noexcept {
            return x() * other.y() - y() * other.x();
        }

        template<typename U = T>
        constexpr typename std::enable_if_t<Dim == 3, VecBase<U, Dim>> cross(const VecBase<U, Dim> &other) const noexcept {
            return VecBase<T, Dim>({
                  y() * other.z() - z() * other.y(),
                  z() * other.x() - x() * other.z(),
                  x() * other.y() - y() * other.x()
            });
        }

    };

    template<typename U, std::size_t D>
    constexpr std::ostream& operator <<(std::ostream& os, const VecBase<U, D> &vec) noexcept {
        os << "(";
        if constexpr (D > 0) {
            os << vec[0];
            for (std::size_t i = 1; i < D; ++i) {
                os << ", " << vec[i];
            }
        }
        os << ")";
        return os;
    }

    // ---
    // Easy aliases
    // ---

    template<typename T, std::size_t Dim>
    using Vec = VecBase<T, Dim>;

    template<std::size_t Dim>
    using VecR = Vec<double, Dim>;

    template<typename T>
    using Vec2 = Vec<T, 2>;

    template<typename T>
    using Vec3 = Vec<T, 3>;

    using VecR2 = Vec2<double>;

    using VecR3 = Vec3<double>;

}

#endif
