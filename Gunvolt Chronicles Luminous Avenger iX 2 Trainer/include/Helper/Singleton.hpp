#pragma once

#include <memory>

namespace GCLAX2
{
    // Curiously Recurring Template Pattern (CRTP)
    template<typename Dervied>
    class Singleton
    {
        static std::shared_ptr<Dervied> obj; // should be initialized
    public:
        template<typename... Args>
        static std::shared_ptr<Dervied> get(Args... args) noexcept
        {
            if (obj == nullptr)
            {
                Singleton<Dervied>:: obj = { new Dervied{ args... } };
            }
            return obj;
        }
    };
}