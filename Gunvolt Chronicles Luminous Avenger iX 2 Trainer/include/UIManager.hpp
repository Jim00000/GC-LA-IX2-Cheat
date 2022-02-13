#pragma once

#include <d3d9.h>

namespace GCLAX2
{
    class UIManager
    {
        IDirect3DDevice9* d3dev_ = nullptr;
        HWND hWnd_ = nullptr;
        LONG_PTR oldWndProc_ = NULL;
    public:
        UIManager() noexcept;

        void initialize() noexcept;
    };
}