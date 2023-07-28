
#pragma once

#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>

#define ThrowIfFailed(x)                                              \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    std::wstring wfn = AnsiToWString(__FILE__);                       \
    if(FAILED(hr__)) { throw DxException(hr__, L#x, wfn, __LINE__); } \
}

#define ReturnIfFailed(x)                                             \
{                                                                     \
    HRESULT hr__ = (x);                                               \
    if(FAILED(hr__)) { return; }                                      \
}
