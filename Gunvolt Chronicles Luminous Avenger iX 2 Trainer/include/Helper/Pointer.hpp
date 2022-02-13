#pragma once

#include <cstddef>
#include <type_traits>

namespace GCLAX2
{
    class Pointer
    {
        unsigned char* address;

    public:
        template <typename T>
            requires requires (T)
        {
            !std::is_same_v<T, unsigned char*>;
            std::is_scalar_v<T>;
            std::is_nothrow_convertible_v<T, unsigned char*>;
        }
        Pointer(T address) noexcept : Pointer{ reinterpret_cast<unsigned char*>(address) } {}

        Pointer(unsigned char* address);

        template <typename Type>
        Type to() const noexcept
        {
            unsigned char* addr = (unsigned char*)this->address;
            return reinterpret_cast<Type>(this->address);
        }

        const Pointer dereference() const;

        const Pointer offset(const std::ptrdiff_t delta) const noexcept;
    };
}