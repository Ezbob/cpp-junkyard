#ifndef HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8
#define HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8

#include <cmath>
#include <ostream>

namespace LinAlg {

    template<typename T, std::size_t Dim>
    class VecBase {

    protected:
        T _data[Dim] = {0};

    public:
        constexpr static std::size_t dimension = Dim;

        constexpr VecBase() noexcept {};

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
            return VecBase<T, Dim>::initWith(0);
        }

        constexpr static VecBase<T, Dim> ones() noexcept {
            return VecBase<T, Dim>::initWith(1);
        }

        constexpr T operator[](std::size_t i) const noexcept {
            return _data[i];
        }

        constexpr VecBase<T, Dim> add(const VecBase<T, Dim> &other) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + other._data[i];
            }
            return result;
        }

        constexpr VecBase<T, Dim> add(const T &scalar) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + scalar;
            }
            return result;
        }

        constexpr VecBase<T, Dim> sub(const T &scalar) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] - scalar;
            }
            return result;
        }

        constexpr VecBase<T, Dim> sub(const VecBase<T, Dim> &other) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] + other._data[i];
            }
            return result;
        }

        constexpr VecBase<T, Dim> mul(const T &scalar) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] * scalar;
            }
            return result;
        }

        constexpr VecBase<T, Dim> mul(const VecBase<T, Dim> &other) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] * other._data[i];
            }
            return result;
        }

        constexpr VecBase<T, Dim> div(const T &scalar) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] / scalar;
            }
            return result;
        }

        constexpr VecBase<T, Dim> div(const VecBase<T, Dim> &other) const noexcept {
            VecBase<T, Dim> result;
            for (std::size_t i = 0; i < Dim; ++i) {
                result._data[i] = _data[i] / other._data[i];
            }
            return result;
        }

        constexpr VecBase<T, Dim> operator +(const VecBase<T, Dim> &other) const noexcept {
            return add(other);
        }

        constexpr VecBase<T, Dim> operator -(const VecBase<T, Dim> &other) const noexcept {
            return add(other);
        }

        constexpr VecBase<T, Dim> operator *(const T &other) const noexcept {
            return mul(other);
        }

        constexpr VecBase<T, Dim> operator /(const T &other) const noexcept {
            return div(other);
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

        constexpr T *begin() const noexcept {
            return &_data[0];
        }

        constexpr T *end() const noexcept {
            return &_data[Dim];
        }

        template<typename U, std::size_t D>
        friend constexpr std::ostream& operator <<(std::ostream&, const VecBase<U, D>&) noexcept;
    };

    template<typename U, std::size_t D>
    constexpr std::ostream& operator <<(std::ostream& os, const VecBase<U, D> &vec) noexcept {
        os << "(";
        if (vec.dimension > 0) {
            os << vec[0];
            for (std::size_t i = 1; i < vec.dimension; ++i) 
                os << ", " << vec[i];
        }
        os << ")";
        return os;
    }

    template<typename T, std::size_t Dim>
    class Vec : public VecBase<T, Dim> {

    public:
        constexpr Vec() noexcept {};

        constexpr explicit Vec(const T(&args)[Dim]) noexcept : VecBase<T, Dim>(args) {}
    };

    template<typename T>
    class Vec2 : public VecBase<T, 2> {

    public:
        constexpr Vec2() noexcept {}

        constexpr explicit Vec2(const T(&args)[2]) noexcept : VecBase<T, 2>(args) {}

        constexpr int superCool2DMethod() const noexcept {
            return 42;
        }
    };

    // ---
    // Easy aliases
    // ---

    template<std::size_t Dim>
    using VecR = Vec<double, Dim>;

    using VecR2 = Vec2<double>;

    template<typename T>
    using Vec3 = Vec<T, 3>;

    using VecR3 = Vec<double, 3>;

}

#endif
