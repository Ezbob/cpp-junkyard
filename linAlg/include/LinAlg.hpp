#ifndef HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8
#define HEADER_GUARD_555f3585de52793a2e4eb2d7704775f8

#include <cmath>
#include <ostream>
#include <functional>

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

    template<typename T, std::size_t Dim, VectorEqualsComparator_t<T, Dim> EqualsComparator = DefaultVectorEqualsComparator<T, Dim>>
    struct VecBase {
        T _data[Dim] = {0};
        constexpr static std::size_t dim = Dim;

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
            return VecBase<T, Dim>::initWith(0);
        }

        constexpr static VecBase<T, Dim> ones() noexcept {
            return VecBase<T, Dim>::initWith(1);
        }

        constexpr T operator[](std::size_t i) const noexcept {
            return _data[i];
        }

        T operator[](std::size_t i) noexcept {
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
                result._data[i] = _data[i] - other._data[i];
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

        constexpr VecBase<T, Dim> operator +(const T &scalar) const noexcept {
            return add(scalar);
        }

        constexpr VecBase<T, Dim> operator -(const VecBase<T, Dim> &other) const noexcept {
            return sub(other);
        }

        constexpr VecBase<T, Dim> operator -(const T &scalar) const noexcept {
            return sub(scalar);
        }

        constexpr VecBase<T, Dim> operator *(const T &other) const noexcept {
            return mul(other);
        }

        constexpr VecBase<T, Dim> operator *(const VecBase<T, Dim> &other) const noexcept {
            return mul(other);
        }

        constexpr VecBase<T, Dim> operator /(const T &other) const noexcept {
            return div(other);
        }

        constexpr VecBase<T, Dim> operator /(const VecBase<T, Dim> &other) const noexcept {
            return div(other);
        }

        constexpr bool operator ==(const VecBase<T, Dim> &other) const noexcept {
            return EqualsComparator(_data, other._data);
        }

        constexpr bool operator !=(const VecBase<T, Dim> &other) const noexcept {
            return !EqualsComparator(_data, other._data);
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
        if (vec.dim > 0) {
            os << vec[0];
            for (std::size_t i = 1; i < vec.dim; ++i) 
                os << ", " << vec[i];
        }
        os << ")";
        return os;
    }

    template<typename T>
    class Vec2 : public VecBase<T, 2> {
        using BaseClass = VecBase<T, 2>;

    public:
        constexpr Vec2() noexcept {}

        constexpr explicit Vec2(const T(&args)[2]) noexcept : BaseClass(args) {}

        constexpr T x() const noexcept {
            return BaseClass::_data[0];
        }

        constexpr T y() const noexcept {
            return BaseClass::_data[1];
        }

        /**
         * The 2D cross product hack.
         * It's really the z-component of 3D vector perpendicular to the two 2D vectors
         * that the product is calculated from.
         * Zero value here means that the two vectors are co-linear
         */
        constexpr T cross(const Vec2<T> &other) const noexcept {
            return (x() * other.y()) - (y() * other.x());
        }
    };

    template<typename T>
    class Vec3 : public VecBase<T, 3> {
        using BaseClass = VecBase<T, 3>;

    public:
        constexpr Vec3() noexcept {}

        constexpr explicit Vec3(const T(&args)[3]) noexcept : BaseClass(args) {}

        constexpr T x() const noexcept {
            return BaseClass::_data[0];
        }

        constexpr T y() const noexcept {
            return BaseClass::_data[1];
        }

        constexpr T z() const noexcept {
            return BaseClass::_data[2];
        }

        constexpr Vec3<T> cross(const Vec3<T> &other) const noexcept {
            return Vec3<T>({
                  y() * other.z() - z() * other.y()
                , z() * other.x() - x() * other.z()
                , x() * other.y() - y() * other.x()
            });
        }
    };

    // ---
    // Easy aliases
    // ---

    template<typename T, std::size_t Dim>
    using Vec = VecBase<T, Dim>;

    template<std::size_t Dim>
    using VecR = Vec<double, Dim>;

    using VecR2 = Vec2<double>;

    template<typename T>
    using Vec3 = Vec3<T>;

    using VecR3 = Vec3<double>;


    // ---
    // Matrix
    // ---

    template<typename T, std::size_t Row, std::size_t Column = Row>
    struct MatBase {
        static constexpr std::size_t rows = Row;
        static constexpr std::size_t columns = Column;
        T _data[Row * Column] = {0};

        constexpr MatBase() noexcept = default;

        constexpr explicit MatBase(const T (&arg)[Row][Column]) noexcept {
            for (std::size_t i = 0; i < Row; ++i) {
                for (std::size_t j = 0; j < Column; ++j) {
                    _data[i * Row + j] = arg[i][j];
                }
            }
        }

        constexpr explicit MatBase(const VecBase<T, Column> (&arg)[Row]) noexcept {
            for (std::size_t i = 0; i < Row; ++i) {
                for (std::size_t j = 0; j < Column; ++j) {
                    _data[i * Row + j] = arg[i][j];
                }
            }
        }

        constexpr explicit MatBase(const T(&arg)[Row * Column]) noexcept {
            for (std::size_t i = 0; i < Row * Column; ++i) {
                _data[i] = arg[i];
            }
        }

        constexpr MatBase<T, Row, Column> add(const MatBase<T, Row, Column> &other) noexcept {
            MatBase<T, Row, Column> result;
            for (std::size_t i = 0; i < Row; ++i) {
                for (std::size_t j = 0; j < Column; ++j) {
                    result._data[i * Row + j] = _data[i * Row + j] + other._data[i * Row + j];
                }
            }

            return result;
        }

        constexpr MatBase<T, Row, Column> sub(const MatBase<T, Row, Column> &other) noexcept {
            MatBase<T, Row, Column> result;
            for (std::size_t i = 0; i < Row; ++i) {
                for (std::size_t j = 0; j < Column; ++j) {
                    result._data[i * Row + j] += _data[i * Row + j] - other._data[i * Row + j];
                }
            }

            return result;
        }


        constexpr MatBase<T, Row, Column> operator +(const MatBase<T, Row, Column> &other) noexcept {
            return add(other);
        }

        constexpr MatBase<T, Row, Column> operator -(const MatBase<T, Row, Column> &other) noexcept {
            return sub(other);
        }

        constexpr MatBase<T, Row, Column> transpose() noexcept {
            MatBase<T, Column, Row> result;

            for ( std::size_t i = 0; i < Row; ++i ) {
                for ( std::size_t j = 0; j < Column; ++j ) {
                    result._data[j * Column + i] = _data[i * Row + j];
                }
            }

            return result;
        }

        constexpr static MatBase<T, Row, Column> identity() noexcept {
            static_assert(Row == Column, "Dimension must match for identity matrix");
            MatBase<T, Row, Column> result;
            for ( std::size_t i = 0; i < Row; ++i ) {
                result._data[i * Row + i] = 1;
            }
            return result;
        }

        constexpr T *begin() noexcept {
            return _data[0];
        }

        constexpr T *end() noexcept {
            return _data[Row * Column];
        }

        template<typename U, std::size_t R, std::size_t C>
        friend constexpr std::ostream& operator <<(std::ostream&, const MatBase<U, R, C>&) noexcept;
    };

    template<typename U, std::size_t R, std::size_t C>
    constexpr std::ostream& operator <<(std::ostream& os, const MatBase<U, R, C> &mat) noexcept {
        os << "{";

        for ( std::size_t i = 0; i < R; ++i ) {
            os << "{";
            for (std::size_t j = 0; j < C; ++j) {
                os << mat._data[i * R + j];
                if (j < (C - 1)) os << ", ";
            }
            if (i < (R - 1)) os << "},\n"; else os << "}";
        }

        os << "}";
        return os;
    }


    template<typename T, std::size_t R, std::size_t C = R>
    using Mat = MatBase<T, R, C>;

    template<std::size_t R, std::size_t C = R>
    using MatR = MatBase<double, R, C>; 

}

#endif
