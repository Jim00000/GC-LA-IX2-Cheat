#include <fstream>
#include <iostream>

#include <Windows.h>
#include <tlhelp32.h>
#include <processthreadsapi.h>
#include <spdlog/spdlog.h>

#include "Helper/ProcessInformation.hpp"
#include "Helper/Pointer.hpp"
#include "CheatLogger.hpp"
#include "CheatException.hpp"
#include "GameVersion.hpp"

using namespace GCLAX2;

GameVersion::GameVersion() noexcept
{
    ProcessInformation procInfo {};
    unsigned char* gameBaseAddr = procInfo.getProcessBaseAddress();
    const char* const gameVersion = Pointer{ gameBaseAddr }
        .offset(0x0188F5E8).dereference()
        .offset(0x50).dereference()
        .offset(0x20).dereference()
        .offset(0x168).dereference()
        .offset(0x10).dereference()
        .offset(0xD0).dereference()
        .offset(0x860).to<const char*>();

    this->version_ = std::string(gameVersion);
    spdlog::debug("Game version : {}", this->version_);
}

void GameVersion::verify() const
{
    // We only support v1.1.2 right now !
    if (version_.compare("1.1.2") != 0)
    {
        spdlog::critical("game version mismatch");
        throw VersionMismatchError {};
    }
}

const std::string GCLAX2::GameVersion::get() const noexcept
{
    return this->version_;
}
