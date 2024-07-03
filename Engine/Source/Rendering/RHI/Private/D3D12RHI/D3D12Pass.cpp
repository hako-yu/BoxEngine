#include "D3D12RHI/D3D12Pass.h"

#include "D3D12RHI/D3D12Adapter.h"
#include "D3D12RHI/D3D12Device.h"
#include "D3D12RHI/D3D12CommandList.h"
#include "D3D12RHI/D3D12Viewport.h"

FD3D12Pass::FD3D12Pass(FD3D12Adapter* ParentAdapter)
	: FD3D12AdapterChild(ParentAdapter)
{

}

FD3D12Pass::~FD3D12Pass()
{

}

void FD3D12Pass::Run()
{
	FD3D12Device* Device = ParentAdapter->GetRootDevice();
	FD3D12Viewport* MainViewport = ParentAdapter->GetMainViewport();

	FD3D12CommandQueue* CmdQueue = Device->GetRootQueue();
	FD3D12CommandAllocator* CmdAllocator = Device->GetDefaultCommandAllocator();
	FD3D12CommandList* CmdList = Device->GetDefaultCommandList();

	// Reset CmdList
	CmdAllocator->Reset();
	CmdList->Reset(CmdAllocator);

	// Pre Run

	// Run

	// Post Run
	MainViewport->PresentBackBuffer();
	// MainViewport->UploadLastBackBuffer(CmdList);
	CmdQueue->ExecuteCommandList(CmdList);

	// Present
	MainViewport->Present();

	// Flush CmdQueue
	CmdQueue->Flush();
}
