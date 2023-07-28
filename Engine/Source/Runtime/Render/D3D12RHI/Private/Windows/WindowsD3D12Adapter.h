
#pragma once

#include "D3D12Adapter.h"
#include "WindowsD3D12Util.h"

class FWindowsD3D12Adapter : public FD3D12Adapter
{
public:
	FWindowsD3D12Adapter();
	~FWindowsD3D12Adapter();

protected:
	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
};
