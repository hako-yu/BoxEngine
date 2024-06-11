#pragma once

#include <string>

#include <wrl.h>
#include <dxgi.h>
#include <d3d12.h>
#include <D3Dcompiler.h>

using namespace Microsoft::WRL;

class DxException
{
public:
    DxException() = default;
};

#define ThrowIfFailed(hr) \
if (FAILED(hr)) { throw DxException();}
