#pragma once

#include <string>

namespace GCLAX2
{
    class GameVersion
    {
        std::string version_;
    public:
        GameVersion() noexcept;

        void verify() const;

        const std::string get() const noexcept;
    };
}