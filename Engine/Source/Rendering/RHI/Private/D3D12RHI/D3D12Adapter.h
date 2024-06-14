#pragma once

#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12Device;

class FD3D12Adapter
{
public:
	FD3D12Adapter();
	~FD3D12Adapter();

public:
	void InitRootDevice();

	FD3D12Device* GetRootDevice() { return RootDevice; }

protected:
	FD3D12Device* RootDevice = nullptr;

public:
	IDXGIFactory* GetDxFactory() { return DxFactory.Get(); }
	IDXGIAdapter* GetDxAdapter() { return DxAdapter.Get(); }

private:
	ComPtr<IDXGIFactory> DxFactory;
	ComPtr<IDXGIAdapter> DxAdapter;
};
