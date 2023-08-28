
#include "D3D12CommandQueue.h"

#include "D3D12Device.h"

FD3D12CommandQueueContext::FD3D12CommandQueueContext(FD3D12Device* InDevice)
{
	ID3D12Device* DxDevice = InDevice->GetDxDevice();

	ThrowIfFailed(DxDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(DxCommandAllocator.GetAddressOf())));

	ThrowIfFailed(DxDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		DxCommandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(DxCommandList.GetAddressOf())));
}

FD3D12CommandQueueContext::~FD3D12CommandQueueContext()
{

}

FD3D12CommandQueue::FD3D12CommandQueue(FD3D12Device* InDevice)
{
	ID3D12Device* DxDevice = InDevice->GetDxDevice();

	D3D12_COMMAND_QUEUE_DESC QueueDesc = {};
	QueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	QueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	ThrowIfFailed(DxDevice->CreateCommandQueue(&QueueDesc, IID_PPV_ARGS(&DxCommandQueue)));

	for (uint8 i = 0; i < ContextCount; i++)
	{
		ContextList.Add(FD3D12CommandQueueContext(InDevice));
	}
}

FD3D12CommandQueue::~FD3D12CommandQueue()
{

}
