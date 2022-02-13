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
        .offset(0x014743F8).dereference()
        .offset(0x388).dereference()
        .offset(0x2A8).dereference()
        .offset(0xCF0).to<const char*>();

    this->version_ = std::string(gameVersion);
    spdlog::debug("Game version : {}", this->version_);
}

void GameVersion::verify() const
{
    // We only support v1.1.2 right now !
    if (version_.compare("1.1.2") != 0)
    {
        throw VersionMismatchError {};
    }
}

const std::string GCLAX2::GameVersion::get() const noexcept
{
    return this->version_;
}
