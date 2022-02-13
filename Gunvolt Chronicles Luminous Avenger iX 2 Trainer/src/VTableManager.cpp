#include <d3d9.h>
#include "VTableManager.hpp"

using namespace GCLAX2;

std::shared_ptr<VTableManager<IDirect3DDevice9>> Singleton<VTableManager<IDirect3DDevice9>>::obj = nullptr;