#pragma once

#include <functional>
#include <memory>
#include <spdlog/spdlog.h>

#include "Helper/Singleton.hpp"

namespace GCLAX2
{
    class CheatLogger : Singleton<CheatLogger>
    {
    private:
        CheatLogger();

        void redirectStream() const noexcept;

    public:

        virtual ~CheatLogger() noexcept;

        CheatLogger(const CheatLogger&) = delete;

        CheatLogger& operator=(const CheatLogger&) = delete;

        CheatLogger(CheatLogger&&) = delete;

        CheatLogger& operator=(CheatLogger&&) = delete;

        void openConsole() const noexcept;

        void closeConsole() const noexcept;

        friend static std::shared_ptr<CheatLogger> Singleton<CheatLogger>::get() noexcept;
    };
}