#include <Windows.h>
#include <spdlog/spdlog.h>

#include "CheatManager.hpp"
#include "CheatLogger.hpp"

#include <d3d9.h>

using namespace GCLAX2;

BOOL WINAPI Dll_Process_Attach()
{
    // Open debug console
    auto logger = Singleton<CheatLogger>::get();
    logger->openConsole();
    spdlog::set_level(spdlog::level::trace);

    auto manager = Singleton<CheatManager>::get();
    manager->initialize();

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason,LPVOID lpReserved)
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        Dll_Process_Attach();
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}