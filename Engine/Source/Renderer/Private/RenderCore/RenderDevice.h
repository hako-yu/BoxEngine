#pragma once

#include <wrl.h>
#include <dxgi.h>
#include <d3d12.h>

using namespace Microsoft::WRL;

class FRenderDevice
{
public:
	void Init();

public:
	IDXGIFactory* GetDxFactory() { return DxFactory.Get(); }
	ID3D12Device* GetDxDevice() { return DxDevice.Get(); }

private:
	ComPtr<IDXGIFactory> DxFactory;
	ComPtr<IDXGIAdapter> DxAdapter;
	ComPtr<ID3D12Device> DxDevice;
};
