#include "D3D12RHI/D3D12CommandList.h"

#include "D3D12RHI/D3D12Device.h"

// Command Queue
#pragma region FD3D12CommandQueue
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

	HRes = DxDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&DxFence));
	ThrowIfFailed(HRes);
}

FD3D12CommandQueue::~FD3D12CommandQueue()
{
	DxCommandQueue.Reset();
}

void FD3D12CommandQueue::ExecuteCommandList(FD3D12CommandList* CommandList)
{
	CommandList->GetDxCommandList()->Close();
	ID3D12CommandList* CmdLists[] = { CommandList->GetDxCommandList() };
	DxCommandQueue->ExecuteCommandLists(1, CmdLists);

	CurrentFenceNum++;
	CommandList->RefreshFenceNum(DxFence.Get(), CurrentFenceNum);
}

void FD3D12CommandQueue::Flush()
{
	DxCommandQueue->Signal(DxFence.Get(), CurrentFenceNum);
}
#pragma endregion

// Command Allocator
#pragma region FD3D12CommandAllocator
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

void FD3D12CommandAllocator::Flush()
{
	if (!Fence) return;

	if (Fence->GetCompletedValue() < FenceNum)
	{
		HANDLE Handle = CreateEventEx(nullptr, nullptr, CREATE_EVENT_INITIAL_SET, EVENT_ALL_ACCESS);
		if (Handle)
		{
			HRESULT HRes;
			HRes = Fence->SetEventOnCompletion(FenceNum, Handle);
			ThrowIfFailed(HRes);

			WaitForSingleObject(Handle, INFINITE);

			CloseHandle(Handle);
		}
		else
		{
			ThrowIfFailed(GetLastError());
		}
	}

	HRESULT HRes;
	HRes = DxCommandAllocator->Reset();
	ThrowIfFailed(HRes);
}

void FD3D12CommandAllocator::SetFence(ID3D12Fence* NewFence, int NewFenceNum)
{
	Fence = NewFence;
	FenceNum = NewFenceNum;
}
#pragma endregion

// Command List
#pragma region FD3D12CommandList
FD3D12CommandList::FD3D12CommandList(FD3D12CommandAllocator* Allocator, FD3D12Device* ParentDevice)
	: FD3D12DeviceChild(ParentDevice)
	, CmdAllocator(Allocator)
{
	ID3D12Device* DxDevice = ParentDevice->GetDxDevice();

	HRESULT HRes;
	HRes = DxDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		CmdAllocator->GetDxCommandAllocator(),
		nullptr,
		IID_PPV_ARGS(&DxCommandList));
	ThrowIfFailed(HRes);

	DxCommandList->Close();
}

FD3D12CommandList::~FD3D12CommandList()
{
	DxCommandList.Reset();
}

void FD3D12CommandList::Reset(FD3D12CommandAllocator* Allocator)
{
	CmdAllocator = Allocator;
	DxCommandList->Reset(CmdAllocator->GetDxCommandAllocator(), nullptr);
}

void FD3D12CommandList::RefreshFenceNum(ID3D12Fence* NewFence, int NewFenceNum)
{
	CmdAllocator->SetFence(NewFence, NewFenceNum);
}
#pragma endregion
