
#include "D3D12Adapter.h"

#include "D3D12Device.h"
#include "D3D12Viewport.h"

FD3D12Adapter::FD3D12Adapter(IDXGIAdapter* InDxAdapter)
	: DxAdapter(InDxAdapter)
{

}

FD3D12Adapter::~FD3D12Adapter()
{
	if (Device)
	{
		delete Device;
	}

	for (FD3D12Viewport* Viewport : Viewports)
	{
		delete Viewport;
	}
	Viewports.clear();
}

void FD3D12Adapter::SetupDevice()
{
	Device = new FD3D12Device(this);
	Device->Setup();
}

FD3D12Viewport* FD3D12Adapter::CreateViewport(HWND WindowHanle, uint32 SizeX, uint32 SizeY)
{
	FD3D12Viewport* Viewport = new FD3D12Viewport(this, WindowHanle, SizeX, SizeY);
	Viewports.Add(Viewport);
	return Viewport;
}
