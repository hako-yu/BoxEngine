#pragma once

#include "CoreMinimal.h"
#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12Device;
class FD3D12Viewport;
class FD3D12Pass;

class FD3D12Adapter
{
public:
	FD3D12Adapter();
	~FD3D12Adapter();

public:
	void InitRootDevice();
	FD3D12Viewport* CreateMainViewport();

	FD3D12Device* GetRootDevice() { return RootDevice; }
	FD3D12Viewport* GetMainViewport() { return MainViewport; }
	FD3D12Pass* FindOrAddPass(ERHIPassType PassType);
protected:
	FD3D12Device* RootDevice = nullptr;
	FD3D12Viewport* MainViewport = nullptr;
	TMap<ERHIPassType, FD3D12Pass*> PassLibrary;

public:
	IDXGIFactory* GetDxFactory() { return DxFactory.Get(); }
	IDXGIAdapter* GetDxAdapter() { return DxAdapter.Get(); }
private:
	ComPtr<IDXGIFactory> DxFactory;
	ComPtr<IDXGIAdapter> DxAdapter;
};
