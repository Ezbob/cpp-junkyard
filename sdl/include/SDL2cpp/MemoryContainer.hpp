#ifndef HEADER_GUARD_f608888504445bd55db8b149f35cfa17
#define HEADER_GUARD_f608888504445bd55db8b149f35cfa17

#include <memory>
#include <iostream>
#include "SDL2cpp/ErrorCheck.hpp"

template<typename T>
using FreeingFunction_t = void (*)(T *);

template<class Derived, typename ContainedType, FreeingFunction_t<ContainedType> FreeingFunction>
class ContainerBase {

protected:
    constexpr static FreeingFunction_t<ContainedType> freeingFunction = FreeingFunction;

    ContainedType *m_contained;
    bool m_isLoaded = false;

public:
    ~ContainerBase() {
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
        return m_contained != nullptr;
    }

    constexpr void load(ContainedType *newStuff) {
        m_contained = newStuff;
    }
};

template<class Derived, typename ContainedType, FreeingFunction_t<ContainedType> FreeingFunction>
class SharedContainerBase {

protected:
    constexpr static FreeingFunction_t<ContainedType> freeingFunction = FreeingFunction;

    std::shared_ptr<ContainedType> m_contained = nullptr;

public:
    constexpr explicit operator ContainedType *() {
        return m_contained.get();
    }

    constexpr operator const ContainedType *() {
        return m_contained.get();
    }

    constexpr bool isLoaded() const {
        return m_contained != nullptr;
    }

    constexpr void load(ContainedType *newStuff) {
        m_contained = std::shared_ptr<ContainedType>(newStuff, FreeingFunction);
    }
};

#endif
