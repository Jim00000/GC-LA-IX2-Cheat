#pragma once

#include "Helper/Singleton.hpp"

namespace GCLAX2
{
    class CheatUIRender : Singleton<CheatUIRender>
    {
        bool fixedHP_;
    private:
        CheatUIRender() noexcept = default;

    public:
        virtual ~CheatUIRender() noexcept;

        CheatUIRender(const CheatUIRender&) = delete;

        CheatUIRender& operator=(const CheatUIRender&) = delete;

        CheatUIRender(CheatUIRender&&) = delete;

        CheatUIRender& operator=(CheatUIRender&&) = delete;

        void render() noexcept;

        friend static std::shared_ptr<CheatUIRender> Singleton<CheatUIRender>::get() noexcept;
    };
}