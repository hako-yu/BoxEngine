
#include "D3D12RHI.h"

#include "D3D12Utils.h"
#include "D3D12Adapter.h"
#include "D3D12Viewport.h"

FD3D12RHI::FD3D12RHI()
{
	ThrowIfFailed(CreateDXGIFactory(IID_PPV_ARGS(&DxgiFactory2)));
}

FD3D12RHI::~FD3D12RHI()
{
	for (FD3D12Adapter* Adapter : AdapterList)
	{
		delete Adapter;
	}
	AdapterList.clear();
}

void FD3D12RHI::Init()
{
	IDXGIAdapter* TmpAdapter;
	for (UINT i = 0; DxgiFactory2->EnumAdapters(i, &TmpAdapter) != DXGI_ERROR_NOT_FOUND; i++)
	{
		FD3D12Adapter* Adapter = new FD3D12Adapter(TmpAdapter);
		AdapterList.Add(Adapter);
	}

	if (AdapterList.Num() > 0)
	{
		CurrentAdapter = AdapterList[0];
	}

	for (FD3D12Adapter* Adapter : AdapterList)
	{
		Adapter->SetupDevice();
	}
}

FRHIViewport* FD3D12RHI::CreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY)
{
	return CurrentAdapter->CreateViewport((HWND)WindowHandle, SizeX, SizeY);
}
