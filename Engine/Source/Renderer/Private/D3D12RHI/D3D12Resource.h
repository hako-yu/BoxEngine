#pragma once

#include "D3D12RHI/D3D12Common.h"
#include <vector>

class FD3D12CommandList;

class FD3D12Heap
{
private:
	D3D12_HEAP_TYPE Type;

private:
	ComPtr<ID3D12Heap> DxHeap;
};

class FD3D12Resource
{
private:
	D3D12_RESOURCE_STATES State;
	ComPtr<FD3D12Heap> Heap;

private:
	ComPtr<ID3D12Resource> DxResource;
};

class FD3D12ReourceBarrierBatcher
{
	struct FD3D12ResourceBarrier : public D3D12_RESOURCE_BARRIER
	{
		FD3D12ResourceBarrier() = default;
	};

public:
	void AddTransition(FD3D12Resource* InResource, D3D12_RESOURCE_STATES BeforeState, D3D12_RESOURCE_STATES AfterState);
	void FlushIntoCommandList(FD3D12CommandList* CommandList);

private:
	std::vector<FD3D12ResourceBarrier> Barriers;
};
