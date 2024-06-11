#pragma once

#include "RHICore/RHICommandList.h"
#include "D3D12RHI/D3D12Device.h"
#include "D3D12RHI/D3D12Common.h"

class FD3D12CommandQueue : public FRHICommandQueue, public FD3D12DeviceChild
{
public:
	FD3D12CommandQueue(FD3D12Device* Device);
	~FD3D12CommandQueue();

private:
	ComPtr<ID3D12CommandQueue> DxCommandQueue;
};

class FD3D12CommandList : public FRHICommandList, public FD3D12DeviceChild
{
public:
	FD3D12CommandList(FD3D12Device* Device);
	~FD3D12CommandList();

private:
	ComPtr<ID3D12CommandList> DxCommandList;
};
