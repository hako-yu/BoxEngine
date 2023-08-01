
#pragma once

#include "D3D12Minimal.h"

class FD3D12Device;

class FD3D12CommandList
{
public:
	static FD3D12CommandList* Create(FD3D12Device* InDevice);
	void Release();

	ID3D12CommandQueue* GetCmdQueue() { return DxCommandQueue.Get(); }

public:
	void Reset();
	void Execute();

protected:
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> DxCommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> DxDirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> DxCommandList;
};
