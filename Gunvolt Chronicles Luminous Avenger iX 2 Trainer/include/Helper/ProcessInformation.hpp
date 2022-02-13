#pragma once

#include <Windows.h>

namespace GCLAX2
{
    class ProcessInformation
    {
    public:
        unsigned char* getProcessBaseAddress() noexcept;
    };
}