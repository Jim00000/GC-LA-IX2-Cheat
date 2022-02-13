#include <backends/imgui_impl_dx9.h>
#include <backends/imgui_impl_win32.h>

#include "Hook.hpp"
#include "VTableManager.hpp"
#include "CheatUIRender.hpp"

using namespace GCLAX2;

HRESULT __stdcall GCLAX2::hookEndScene(IDirect3DDevice9* obj) noexcept
{
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Singleton<CheatUIRender>::get()->render();

    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    // Call original IDirect3DDevice9::EndScene
    const static auto mfp = Singleton<VTableManager<IDirect3DDevice9>>::get()->getOriginalMemberFunctionPointer<
        decltype(&IDirect3DDevice9::EndScene)>(obj, static_cast<size_t>(IDirect3DDevice9_VTable_Index::EndScene));
    return (obj->*(mfp))();
}
