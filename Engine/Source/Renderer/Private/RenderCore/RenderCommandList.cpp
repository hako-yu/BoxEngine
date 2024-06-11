#include "RenderCore/RenderCommandList.h"

#include "RenderCore/RenderDevice.h"

void FRenderCommandList::Reset()
{
	DxCommandAllocator->Reset();
}

void FRenderCommandList::Init(FRenderDevice* RenderDevice)
{
	ID3D12Device* DxDevice = RenderDevice->GetDxDevice();

	// Init CommandAllocator
	DxDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&DxCommandAllocator));

	// Init CommandQueue
	D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
	QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	DxDevice->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&DxCommandQueue));

	// Init CommandList
	DxDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		DxCommandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(&DxCommandList));

	// Start off in a closed state.  This is because the first time we refer 
	// to the command list we will Reset it, and it needs to be closed before
	// calling Reset.
	DxCommandList->Close();
}
