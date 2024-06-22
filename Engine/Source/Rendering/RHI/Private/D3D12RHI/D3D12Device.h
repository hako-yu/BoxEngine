#pragma once

#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12Adapter;
class FD3D12CommandQueue;
class FD3D12CommandAllocator;
class FD3D12CommandList;

class FD3D12Device : public FD3D12AdapterChild
{
public:
	FD3D12Device(FD3D12Adapter* ParentAdapter);
	~FD3D12Device();

public:
	void InitRootQueue();
	void InitDefaultCommandList();

	FD3D12CommandQueue* GetRootQueue() { return RootQueue; }

	FD3D12CommandAllocator* GetDefaultCommandAllocator() { return DefaultCommandAllocator; }
	FD3D12CommandList* GetDefaultCommandList() { return DefaultCommandList; }

protected:
	FD3D12CommandQueue* RootQueue = nullptr;

	FD3D12CommandAllocator* DefaultCommandAllocator = nullptr;
	FD3D12CommandList* DefaultCommandList = nullptr;

public:
	ID3D12Device* GetDxDevice() { return DxDevice.Get(); }

private:
	ComPtr<ID3D12Device> DxDevice;
};
