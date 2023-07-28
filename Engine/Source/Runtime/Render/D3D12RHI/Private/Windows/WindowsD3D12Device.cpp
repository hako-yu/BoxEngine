
#include "WindowsD3D12Device.h"

FWindowsD3D12Device::FWindowsD3D12Device()
{
	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,             // default adapter
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&md3dDevice));
}

FWindowsD3D12Device::~FWindowsD3D12Device()
{
	md3dDevice->Release();
}
