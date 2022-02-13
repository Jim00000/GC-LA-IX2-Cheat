#include <Windows.h>
#include <tlhelp32.h>
#include <processthreadsapi.h>

#include "Helper/ProcessInformation.hpp"

using namespace GCLAX2;

unsigned char* ProcessInformation::getProcessBaseAddress() noexcept
{
	const DWORD pid = GetCurrentProcessId();
	const HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, pid);
	MODULEENTRY32 modEntry =
	{
		.dwSize = sizeof(MODULEENTRY32)
	};

	unsigned char* baseAddr = nullptr;

	if (Module32First(hSnapshot, &modEntry))
	{
		baseAddr = modEntry.modBaseAddr;
	}

	return baseAddr;
}