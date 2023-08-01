
#include "D3D12CommandList.h"

#include "D3D12Util.h"
#include "D3D12Device.h"

FD3D12CommandList* FD3D12CommandList::Create(FD3D12Device* InDevice)
{
	FD3D12CommandList* DxCmdList = new FD3D12CommandList();

	if (DxCmdList)
	{
		ID3D12Device* DxDevice = InDevice->Get();
		D3D12_COMMAND_QUEUE_DESC queueDesc = {};
		queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		ThrowIfFailed(DxDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&(DxCmdList->DxCommandQueue))));

		ThrowIfFailed(DxDevice->CreateCommandAllocator(
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			IID_PPV_ARGS(DxCmdList->DxDirectCmdListAlloc.GetAddressOf())));

		ThrowIfFailed(DxDevice->CreateCommandList(
			0,
			D3D12_COMMAND_LIST_TYPE_DIRECT,
			DxCmdList->DxDirectCmdListAlloc.Get(),
			nullptr,
			IID_PPV_ARGS(DxCmdList->DxCommandList.GetAddressOf())));

		// Start off in a closed state.  This is because the first time we refer 
		// to the command list we will Reset it, and it needs to be closed before
		// calling Reset.
		DxCmdList->DxCommandList->Close();
	}
	return DxCmdList;
}

void FD3D12CommandList::Release()
{

}

void FD3D12CommandList::Reset()
{
	// Reuse the memory associated with command recording.
	// We can only reset when the associated command lists have finished execution on the GPU.
	ThrowIfFailed(DxDirectCmdListAlloc->Reset());

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	ThrowIfFailed(DxCommandList->Reset(DxDirectCmdListAlloc.Get(), nullptr));
}

void FD3D12CommandList::Execute()
{
	ThrowIfFailed(DxCommandList->Close());

	// Add the command list to the queue for execution.
	ID3D12CommandList* CmdLists[] = { DxCommandList.Get() };
	DxCommandQueue->ExecuteCommandLists(_countof(CmdLists), CmdLists);
}
