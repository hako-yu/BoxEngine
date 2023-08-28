
#pragma once

#include "CoreMinimal.h"
#include "D3D12Utils.h"

class FD3D12Device;
class FD3D12Viewport;

class FD3D12Adapter
{
public:
	FD3D12Adapter(IDXGIAdapter* InDxAdapter);
	~FD3D12Adapter();

public:
	inline IDXGIAdapter* GetDxAdapter() const { return DxAdapter.Get(); }
	inline FD3D12Device* GetDevice() const { return Device; }

	void SetupDevice();
	FD3D12Viewport* CreateViewport(HWND WindowHanle, uint32 SizeX, uint32 SizeY);

public:
	IDXGIFactory2* DxgiFactory = nullptr;

private:
	FD3D12Device* Device;

	TArray<FD3D12Viewport*> Viewports;

	Microsoft::WRL::ComPtr<IDXGIAdapter> DxAdapter;
};
