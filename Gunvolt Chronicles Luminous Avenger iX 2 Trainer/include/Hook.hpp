#pragma once

#include <d3d9.h>

namespace GCLAX2
{
    enum class IDirect3DDevice9_VTable_Index : size_t
    {
        EndScene = 42
    };

    HRESULT __stdcall hookEndScene(IDirect3DDevice9* obj) noexcept;
}