#pragma once

#include <cstddef>
#include <type_traits>

namespace GCLAX2
{
    class Pointer
    {
        unsigned char* address;
        bool valid_ = true;

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
            if (this->valid_)
                return reinterpret_cast<Type>(this->address);
            else
                return 0;
        }

        const Pointer dereference() const noexcept;

        const Pointer offset(const std::ptrdiff_t delta) const noexcept;

        const Pointer& invalid() noexcept;
    };
}