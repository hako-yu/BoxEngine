#pragma once

#include "CoreMinimal.h"
#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12CommandList;

class FD3D12Heap : public FD3D12DeviceChild
{

};

class FD3D12Resource : public FD3D12DeviceChild
{
public:
	FD3D12Resource(FD3D12Device* ParentDevice,
		const D3D12_HEAP_PROPERTIES* HeapProp,
		const D3D12_RESOURCE_DESC* ResourceDesc,
		D3D12_RESOURCE_STATES InitialState,
		const D3D12_CLEAR_VALUE* ClearValue);
	FD3D12Resource(FD3D12Device* ParentDevice, ID3D12Resource* Resource);
	~FD3D12Resource();

	ID3D12Resource* GetDxResource() { return DxResource.Get(); }

private:
	ComPtr<ID3D12Resource> DxResource;
};

class FD3D12ResourceBarrierBatcher
{
public:
	void AddTransition(FD3D12Resource* Resource, D3D12_RESOURCE_STATES Before, D3D12_RESOURCE_STATES After);
	void FlushIntoCommandList(FD3D12CommandList* CmdList);

	void Reset();

private:
	TArray<D3D12_RESOURCE_BARRIER> Barriers;
};
