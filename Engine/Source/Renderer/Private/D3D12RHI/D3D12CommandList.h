#pragma once

#include "D3D12RHI/D3D12Common.h"

class FD3D12CommandList
{
private:
	ComPtr<ID3D12CommandAllocator> DxCommandAllocator;
	ComPtr<ID3D12CommandQueue> DxCommandQueue;
	ComPtr<ID3D12GraphicsCommandList> DxCommandList;
};
