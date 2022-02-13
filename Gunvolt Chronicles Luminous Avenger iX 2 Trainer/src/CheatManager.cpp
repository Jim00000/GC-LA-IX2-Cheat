#include <spdlog/spdlog.h>
#include "CheatManager.hpp"
#include "CheatException.hpp"

using namespace GCLAX2;

CheatManager::~CheatManager() noexcept
{
}

void CheatManager::initialize() noexcept
{
    try
    {
        // Verify game's version is supported
        version_.verify();
        // Initialize imgui's context
        ui_.initialize();
    }
    catch (const VersionMismatchError&)
    {
        spdlog::critical("Game version mismatches! We only support v1.1.2!");
        exit(EXIT_FAILURE);
    }
    catch (...)
    {
        spdlog::critical("Catch unknown error");
        exit(EXIT_FAILURE);
    }
}

std::shared_ptr<CheatManager> Singleton<CheatManager>::obj = nullptr;