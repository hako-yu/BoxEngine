#pragma once

#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12CommandQueue;
class FD3D12CommandAllocator;
class FD3D12CommandList;

class FD3D12CommandQueue : public FD3D12DeviceChild
{
public:
	FD3D12CommandQueue(FD3D12Device* ParentDevice);
	~FD3D12CommandQueue();

	void ExecuteCommandList(FD3D12CommandList* CommandList);

public:
	ID3D12CommandQueue* GetDxCommandQueue() { return DxCommandQueue.Get(); }

private:
	ComPtr<ID3D12CommandQueue> DxCommandQueue;
};

class FD3D12CommandAllocator : public FD3D12DeviceChild
{
public:
	FD3D12CommandAllocator(FD3D12Device* ParentDevice);
	~FD3D12CommandAllocator();

public:
	ID3D12CommandAllocator* GetDxCommandAllocator() { return DxCommandAllocator.Get(); }

private:
	ComPtr<ID3D12CommandAllocator> DxCommandAllocator;
};

class FD3D12CommandList : public FD3D12DeviceChild
{
public:
	FD3D12CommandList(FD3D12CommandAllocator* Allocator, FD3D12Device* ParentDevice);
	~FD3D12CommandList();

public:
	ID3D12GraphicsCommandList* GetDxCommandList() { return DxCommandList.Get(); }

private:
	ComPtr<ID3D12GraphicsCommandList> DxCommandList;
};
