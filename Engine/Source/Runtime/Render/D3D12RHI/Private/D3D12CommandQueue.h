
#pragma once

#include "CoreMinimal.h"
#include "D3D12Utils.h"

class FD3D12Device;

struct FD3D12CommandQueueContext
{
public:
	FD3D12CommandQueueContext(FD3D12Device* InDevice);
	~FD3D12CommandQueueContext();

private:
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> DxCommandAllocator;
	Microsoft::WRL::ComPtr<ID3D12CommandList> DxCommandList;
};

class FD3D12CommandQueue
{
public:
	FD3D12CommandQueue(FD3D12Device* InDevice);
	~FD3D12CommandQueue();

public:
	inline ID3D12CommandQueue* GetDxCommandQueue() const { return DxCommandQueue.Get(); }

private:
	TArray<FD3D12CommandQueueContext> ContextList;
	uint8 ContextCount = 2;
	uint8 CurrentContextIndex = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> DxCommandQueue;
};
