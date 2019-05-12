#include <iostream>
#include <memory>
#include <functional>

template<typename T>
using FreeingFunction_t = void (*)(T *);

template<typename T>
void doNothingFreeing(T *) {
    // one can free memory here
    std::cout << "I am called" << std::endl;
}

template<class Derived, typename ContainedType, FreeingFunction_t<ContainedType> FreeingFunction>
class ContainerClass {
    ContainedType *m_contained;
    bool m_isLoaded = false;

public:
    ~ContainerClass() {
        if (m_isLoaded) {
            FreeingFunction(m_contained);
        }
    }

    constexpr explicit operator ContainedType *() {
        return m_contained;
    }

    constexpr operator const ContainedType *() {
        return m_contained;
    }

    constexpr bool isLoaded() const {
        return m_isLoaded;
    }

    constexpr void load(ContainedType *newStuff) {
        m_contained = newStuff;
        if (m_contained != nullptr) {
            m_isLoaded = true;
        }
    }
};

template<class Derived, typename ContainedType, FreeingFunction_t<ContainedType> FreeingFunction>
class SharedContainerClass {
    std::shared_ptr<ContainedType> m_contained;
    bool m_isLoaded = false;

public:
    constexpr explicit operator ContainedType *() {
        return m_contained.get();
    }

    constexpr operator const ContainedType *() {
        return m_contained.get();
    }

    constexpr bool isLoaded() const {
        return m_isLoaded;
    }

    constexpr void load(ContainedType *newStuff) {
        m_contained = std::shared_ptr<ContainedType>(newStuff, FreeingFunction);
        if (m_contained != nullptr) {
            m_isLoaded = true;
        }
    }
};

class Derived : public SharedContainerClass<Derived, std::string, doNothingFreeing<std::string> > {};

int main() {
    std::cout << "Starting" << std::endl;

    Derived a;

    std::string string = "Hello world";
    int l = 23;

    a.load(&string);

    if ( a.isLoaded() ) {
        std::cout << *((std::string *) a) << std::endl;
    } else {
        std::cout << "Nothing there" << std::endl;
    }

    return 0;
}