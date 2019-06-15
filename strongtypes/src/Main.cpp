#include <iostream>

namespace strongtypes {
    template<typename T>
    using IsNotReference = typename std::enable_if_t<!std::is_reference_v<T>, void>;

    template<typename T, typename Parameter>
    class NamedType {

    public:
        explicit constexpr NamedType(T const &value) : value_(value) {}

        template<typename T_ = T, typename = IsNotReference<T_>>
        explicit constexpr NamedType(T&& value) : value_(std::move(value)) {}

        // get non-const
        constexpr T& get() {
            return value_;
        }

        // get const
        constexpr std::remove_reference_t<T> const& get() const {
            return value_;
        }

        // we can convert to a ref
        using ref = NamedType<T&, Parameter>;
        operator ref() {
            return ref(value_);
        }

    private:
        T value_;
    };
}

using Area = strongtypes::NamedType<int, struct AreaTag>;
using Width = strongtypes::NamedType<int, struct WidthTag>;
using Height = strongtypes::NamedType<int, struct HeightTag>;

Area calculateRectangleArea(Width w, Height h) {
    return Area(w.get() * h.get());
}

void calculateRectangleArea(Area &out, Width w, Height h) {
    out.get() = w.get() * h.get();
}

int main(int argc, char const *argv[])
{
    Area a = calculateRectangleArea(Width(2), Height(4));

    Area b{0};

    calculateRectangleArea(b, Width(3), Height(4)); 

    std::cout << "Area is: " << a.get() << std::endl;

    std::cout << "Area is: " << b.get() << std::endl;
    return 0;
}
