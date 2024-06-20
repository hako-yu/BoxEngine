#include "D3D12RHI/D3D12Device.h"

#include "D3D12RHI/D3D12Adapter.h"
#include "D3D12RHI/D3D12CommandList.h"

FD3D12Device::FD3D12Device(FD3D12Adapter* ParentAdapter)
	: FD3D12AdapterChild(ParentAdapter)
{
	IDXGIAdapter* DxAdapter = ParentAdapter->GetDxAdapter();

	HRESULT HRes;
	HRes = D3D12CreateDevice(
		DxAdapter,
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&DxDevice)
	);
	ThrowIfFailed(HRes);
}

FD3D12Device::~FD3D12Device()
{
	if (DefaultCommandList) delete DefaultCommandList;
	if (DefaultCommandAllocator) delete DefaultCommandAllocator;
	if (RootQueue) delete RootQueue;

	DxDevice.Reset();
}

void FD3D12Device::InitRootQueue()
{
	RootQueue = new FD3D12CommandQueue(this);
}

void FD3D12Device::InitDefaultCommandList()
{
	DefaultCommandAllocator = new FD3D12CommandAllocator(this);
	DefaultCommandList = new FD3D12CommandList(DefaultCommandAllocator, this);
}
