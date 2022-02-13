#include <cstddef>
#include <type_traits>

#include "Helper/Pointer.hpp"

using namespace GCLAX2;

Pointer::Pointer(unsigned char* address) : address{ address } {}

const Pointer Pointer::dereference() const
{
    unsigned char* addr = reinterpret_cast<unsigned char*>(
        *reinterpret_cast<std::ptrdiff_t*>(this->address));
    return Pointer{ addr };
}

const Pointer Pointer::offset(const std::ptrdiff_t delta) const noexcept
{
    unsigned char* addr = reinterpret_cast<unsigned char*>(
        reinterpret_cast<std::ptrdiff_t>(this->address) + delta);
    return Pointer{ addr };
}