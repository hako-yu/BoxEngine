#include "D3D12RHI/D3D12RHI.h"

#include "D3D12RHI/D3D12Adapter.h"
#include "D3D12RHI/D3D12Device.h"
#include "D3D12RHI/D3D12Viewport.h"

bool FD3D12RHI::Create()
{
	if (FDynamicRHI::Singleton != nullptr)
	{
		return false;
	}

	FDynamicRHI::Singleton = new FD3D12RHI();
	return true;
}

void FD3D12RHI::Init()
{
	InitRootAdapter();
}

void FD3D12RHI::Exit()
{
	delete RootAdapter;
}

FRHIViewport* FD3D12RHI::CreateRHIViewport()
{
	return FD3D12Viewport::Create();
}

void FD3D12RHI::InitRootAdapter()
{
	RootAdapter = new FD3D12Adapter();
	RootAdapter->InitRootDevice();
}
