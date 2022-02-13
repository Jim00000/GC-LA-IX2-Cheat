#include "CheatLogger.hpp"
#include <functional>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <Windows.h>

using namespace GCLAX2;

namespace
{
    constexpr auto LOGGER_NAME = "GCLAX2-LOGGER";
    constexpr auto LOG_FORMAT = "[%Y-%m-%d %H:%M:%S.%e][%^%l%$] %v";
}

CheatLogger::CheatLogger() {}

CheatLogger::~CheatLogger() noexcept
{
    closeConsole();
    spdlog::shutdown();
}

void CheatLogger::redirectStream() const noexcept
{
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
}

void CheatLogger::openConsole() const noexcept
{
    if (AllocConsole())
    {
        redirectStream();
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
        auto cmdLogger = std::make_shared<spdlog::logger>(LOGGER_NAME, sink);
        cmdLogger->set_pattern(LOG_FORMAT);
        cmdLogger->flush_on(spdlog::level::trace);
        spdlog::register_logger(cmdLogger);
        spdlog::set_default_logger(cmdLogger);
        spdlog::set_level(spdlog::level::trace);
    }
}

void CheatLogger::closeConsole() const noexcept
{
    if (FreeConsole())
    {
        redirectStream();
    }
}

std::shared_ptr<CheatLogger> Singleton<CheatLogger>::obj = nullptr;