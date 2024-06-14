#include "D3D12RHI/D3D12CommandList.h"

#include "D3D12RHI/D3D12Device.h"

// Command Queue
FD3D12CommandQueue::FD3D12CommandQueue(FD3D12Device* ParentDevice)
	: FD3D12DeviceChild(ParentDevice)
{
	ID3D12Device* DxDevice = ParentDevice->GetDxDevice();

	D3D12_COMMAND_QUEUE_DESC CmdQueueDesc = {};
	CmdQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	CmdQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	HRESULT HRes;
	HRes = DxDevice->CreateCommandQueue(&CmdQueueDesc, IID_PPV_ARGS(&DxCommandQueue));
	ThrowIfFailed(HRes);
}

FD3D12CommandQueue::~FD3D12CommandQueue()
{
	DxCommandQueue.Reset();
}

// Command Allocator
FD3D12CommandAllocator::FD3D12CommandAllocator(FD3D12Device* ParentDevice)
	: FD3D12DeviceChild(ParentDevice)
{
	ID3D12Device* DxDevice = ParentDevice->GetDxDevice();

	HRESULT HRes;
	HRes = DxDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&DxCommandAllocator));
	ThrowIfFailed(HRes);
}

FD3D12CommandAllocator::~FD3D12CommandAllocator()
{
	DxCommandAllocator.Reset();
}

// Command List
FD3D12CommandList::FD3D12CommandList(FD3D12CommandAllocator* Allocator, FD3D12Device* ParentDevice)
	: FD3D12DeviceChild(ParentDevice)
{
	ID3D12Device* DxDevice = ParentDevice->GetDxDevice();

	HRESULT HRes;
	HRes = DxDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		Allocator->GetDxCommandAllocator(),
		nullptr,
		IID_PPV_ARGS(&DxCommandList));
	ThrowIfFailed(HRes);
}

FD3D12CommandList::~FD3D12CommandList()
{
	DxCommandList.Reset();
}
