
#include "D3D12Device.h"

#include "D3D12Util.h"
#include "D3D12Adapter.h"

FD3D12Device* FD3D12Device::Create(FD3D12Adapter* InAdapter)
{
	FD3D12Device* Device = new FD3D12Device();

	if (Device)
	{
		ThrowIfFailed(D3D12CreateDevice(
			InAdapter ? InAdapter->Get() : nullptr,
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&(Device->DxDevice))));
	}
	return Device;
}
