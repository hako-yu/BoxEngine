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
}

void FD3D12CommandQueue::Flush()
{
	CurrentFenceNum++;
	DxCommandQueue->Signal(DxFence.Get(), CurrentFenceNum);

	if (DxFence->GetCompletedValue() < CurrentFenceNum)
	{
		HANDLE Handle = CreateEvent(nullptr, false, false, nullptr);
		if (Handle)
		{
			HRESULT HRes;
			HRes = DxFence->SetEventOnCompletion(CurrentFenceNum, Handle);
			ThrowIfFailed(HRes);

			WaitForSingleObject(Handle, INFINITE);

			CloseHandle(Handle);
		}
		else
		{
			ThrowIfFailed(GetLastError());
		}
	}
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

void FD3D12CommandAllocator::Reset()
{
	HRESULT HRes;
	HRes = DxCommandAllocator->Reset();
	ThrowIfFailed(HRes);
}
#pragma endregion

// Command List
#pragma region FD3D12CommandList
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

	DxCommandList->Close();
}

FD3D12CommandList::~FD3D12CommandList()
{
	DxCommandList.Reset();
}

void FD3D12CommandList::Reset(FD3D12CommandAllocator* Allocator)
{
	DxCommandList->Reset(Allocator->GetDxCommandAllocator(), nullptr);
}
#pragma endregion
