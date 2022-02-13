#pragma once

#include <string>
#include <stdexcept>

namespace GCLAX2
{
    enum class ExceptionType
    {
        GameVersionMismatch,
        VirtualQueryFail,
        InvalidVirtualTable,
        IndexOutOfBoundVirtualTable,
    };

    template<typename Base, ExceptionType Type>
    class CheatException : Base
    {
    public:
        explicit CheatException<Base, Type>() : Base{ "" } {}
        explicit CheatException<Base, Type>(const std::string& what_arg) : Base{ what_arg } {}
        explicit CheatException<Base, Type>(const char* what_arg) : Base{ what_arg } {}
    };

    using VersionMismatchError = CheatException<std::runtime_error, ExceptionType::GameVersionMismatch>;
    using VirtualQueryError = CheatException<std::runtime_error, ExceptionType::VirtualQueryFail>;
    using InvalidVirtualTableError = CheatException<std::runtime_error, ExceptionType::InvalidVirtualTable>;
    using IndexOutOfBoundVirtualTableError = CheatException<std::runtime_error, ExceptionType::IndexOutOfBoundVirtualTable>;
}