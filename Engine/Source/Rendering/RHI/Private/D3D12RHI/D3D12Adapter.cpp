#include "D3D12RHI/D3D12Adapter.h"

#include "D3D12RHI/D3D12Device.h"
#include "D3D12RHI/D3D12Viewport.h"

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
	if (RootDevice) delete RootDevice;
	if (MainViewport) delete MainViewport;

	DxAdapter.Reset();
	DxFactory.Reset();
}

void FD3D12Adapter::InitRootDevice()
{
	RootDevice = new FD3D12Device(this);
	RootDevice->InitRootQueue();
	RootDevice->InitDefaultCommandList();
}

FD3D12Viewport* FD3D12Adapter::CreateMainViewport()
{
	MainViewport = new FD3D12Viewport(this);
	return MainViewport;
}
