
#pragma once

#include "D3D12Minimal.h"

class FD3D12Adapter
{
public:
	static FD3D12Adapter* Create(IDXGIAdapter* InAdapter);

	IDXGIAdapter* Get() { return DxgiAdapter.Get(); }

protected:
	Microsoft::WRL::ComPtr<IDXGIAdapter> DxgiAdapter;
};
