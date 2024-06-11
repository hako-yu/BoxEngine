#pragma once

#include "D3D12RHI/D3D12Common.h"

class FD3D12Device
{
public:
	FD3D12Device();
	~FD3D12Device();

private:
	ComPtr<IDXGIFactory> DxFactory;
	ComPtr<ID3D12Device> DxDevice;
};

class FD3D12DeviceChild
{
public:
	FD3D12DeviceChild(FD3D12Device* Parent)
		: ParentDevice(Parent)
	{}

protected:
	FD3D12Device* ParentDevice;
};
