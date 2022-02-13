#pragma once

#include "UIManager.hpp"
#include "GameVersion.hpp"
#include "Helper/Singleton.hpp"

namespace GCLAX2
{
    class CheatManager : Singleton<CheatManager>
    {
        GameVersion version_ {};
        UIManager ui_{};

    private:
        CheatManager() noexcept = default;

    public:
        virtual ~CheatManager() noexcept;

        CheatManager(const CheatManager&) = delete;

        CheatManager& operator=(const CheatManager&) = delete;

        CheatManager(CheatManager&&) = delete;

        CheatManager& operator=(CheatManager&&) = delete;

        void initialize() noexcept;

        friend static std::shared_ptr<CheatManager> Singleton<CheatManager>::get() noexcept;
    };
}