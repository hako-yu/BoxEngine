#pragma once

#include <wrl.h>
#include <d3d12.h>

using namespace Microsoft::WRL;

class FRenderDevice;

class FRenderCommandList
{
public:
	void Reset();

public:
	void Init(FRenderDevice* RenderDevice);

public:
	ID3D12CommandAllocator* GetDxCommandAllocator() { return DxCommandAllocator.Get(); }
	ID3D12CommandQueue* GetDxCommandQueue() { return DxCommandQueue.Get(); }
	ID3D12GraphicsCommandList* GetDxCommandList() { return DxCommandList.Get(); }

private:
	ComPtr<ID3D12CommandAllocator> DxCommandAllocator;
	ComPtr<ID3D12CommandQueue> DxCommandQueue;
	ComPtr<ID3D12GraphicsCommandList> DxCommandList;
};
