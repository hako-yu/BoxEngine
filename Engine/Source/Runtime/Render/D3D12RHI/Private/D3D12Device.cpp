
#include "D3D12Device.h"

#include "D3D12Adapter.h"
#include "D3D12CommandQueue.h"

FD3D12Device::FD3D12Device(FD3D12Adapter* Adapter)
{
	ThrowIfFailed(D3D12CreateDevice(
		Adapter->GetDxAdapter(),
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&DxDevice)));
}

FD3D12Device::~FD3D12Device()
{
	if (CommandQueue)
	{
		delete CommandQueue;
	}
}

void FD3D12Device::Setup()
{
	CommandQueue = new FD3D12CommandQueue(this);
}
