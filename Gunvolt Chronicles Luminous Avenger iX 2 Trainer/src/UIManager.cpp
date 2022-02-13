#include <backends/imgui_impl_dx9.h>
#include <backends/imgui_impl_win32.h>
#include <spdlog/spdlog.h>

#include "CheatLogger.hpp"
#include "Helper/ProcessInformation.hpp"
#include "VTableManager.hpp"
#include "UIManager.hpp"
#include "Hook.hpp"

using namespace GCLAX2;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace
{
    LONG_PTR g_defaultWndProc = NULL;
    LRESULT CALLBACK hkWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
            return true;

        if (g_defaultWndProc != NULL)
        {
            return CallWindowProc(reinterpret_cast<WNDPROC>(g_defaultWndProc), hWnd, message, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
}

UIManager::UIManager() noexcept
{
    ProcessInformation info{};
    unsigned char* gameBaseAddr = info.getProcessBaseAddress();
    this->d3dev_ = Pointer{ gameBaseAddr }
        .offset(0x013838F0).dereference()
        .offset(0x0).dereference()
        .offset(0x204).dereference()
        .offset(0x50).dereference()
        .offset(0xD0).dereference()
        .offset(0x538).dereference()
        .offset(0x0).to<IDirect3DDevice9*>();

    D3DDEVICE_CREATION_PARAMETERS params;
    if (FAILED(this->d3dev_->GetCreationParameters(&params)))
    {
        spdlog::critical("Fail to initialize D3DDEVICE_CREATION_PARAMETERS");
        exit(EXIT_FAILURE);
    }
    this->hWnd_ = params.hFocusWindow;
    this->oldWndProc_ = GetWindowLongPtrA(this->hWnd_, GWLP_WNDPROC);
}

void UIManager::initialize() noexcept
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontDefault();
    ImGui::StyleColorsLight();

    ImGui_ImplWin32_Init(this->hWnd_);
    ImGui_ImplDX9_Init(this->d3dev_);

    g_defaultWndProc = this->oldWndProc_;
    SetWindowLongPtrA(this->hWnd_, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hkWndProc));

    spdlog::debug("Pointer to IDirect3DDevice9: 0x{:X}", (UINT64)this->d3dev_);
    const auto hkD3d9 = Singleton<VTableManager<IDirect3DDevice9>>::get(this->d3dev_);
    hkD3d9->hook(static_cast<size_t>(IDirect3DDevice9_VTable_Index::EndScene), hookEndScene);
}

