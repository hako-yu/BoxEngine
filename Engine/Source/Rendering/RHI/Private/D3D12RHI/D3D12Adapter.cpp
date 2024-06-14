#include "D3D12RHI/D3D12Adapter.h"

#include "D3D12RHI/D3D12Device.h"

FD3D12Adapter::FD3D12Adapter()
{
	HRESULT HRes;
	HRes = CreateDXGIFactory(IID_PPV_ARGS(&DxFactory));
	ThrowIfFailed(HRes);

	HRes = DxFactory->EnumAdapters(0, &DxAdapter);
	ThrowIfFailed(HRes);
}

FD3D12Adapter::~FD3D12Adapter()
{
	DxAdapter.Reset();
	DxFactory.Reset();
}

void FD3D12Adapter::InitRootDevice()
{
	RootDevice = new FD3D12Device(this);
	RootDevice->InitRootQueue();
	RootDevice->InitDefaultCommandList();
}
