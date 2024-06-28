#include "D3D12RHI/D3D12RHI.h"

#include "D3D12RHI/D3D12RHICommon.h"
#include "D3D12RHI/D3D12Adapter.h"
#include "D3D12RHI/D3D12Commands.h"

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
	RHICommands = new FD3D12Commands();
}

void FD3D12RHI::Exit()
{
	delete RHICommands;

	if (RootAdapter) delete RootAdapter;
}

void FD3D12RHI::InitRootAdapter()
{
	RootAdapter = new FD3D12Adapter();
	RootAdapter->InitRootDevice();
}

void FD3D12RHI::EnableDebug()
{
	ComPtr<ID3D12Debug> DxDebugController;

	HRESULT HRes;
	HRes = D3D12GetDebugInterface(IID_PPV_ARGS(&DxDebugController));
	ThrowIfFailed(HRes);

	DxDebugController->EnableDebugLayer();
}
