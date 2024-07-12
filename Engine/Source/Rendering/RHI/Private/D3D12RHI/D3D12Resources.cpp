#include "D3D12RHI/D3D12Resources.h"

#include "D3D12RHI/D3D12Device.h"
#include "D3D12RHI/D3D12CommandList.h"

#pragma region FD3D12Resource
FD3D12Resource::FD3D12Resource(FD3D12Device* ParentDevice,
	const D3D12_HEAP_PROPERTIES* HeapProp,
	const D3D12_RESOURCE_DESC* ResourceDesc,
	D3D12_RESOURCE_STATES InitialState,
	const D3D12_CLEAR_VALUE* ClearValue)
	: FD3D12DeviceChild(ParentDevice)
{
	HRESULT HRes;
	HRes = ParentDevice->GetDxDevice()->CreateCommittedResource(
		HeapProp,
		D3D12_HEAP_FLAG_NONE,
		ResourceDesc,
		InitialState,
		ClearValue,
		IID_PPV_ARGS(&DxResource)
	);
	ThrowIfFailed(HRes);
}

FD3D12Resource::FD3D12Resource(FD3D12Device* ParentDevice, ID3D12Resource* Resource)
	: FD3D12DeviceChild(ParentDevice)
	, DxResource(Resource)
{

}

FD3D12Resource::~FD3D12Resource()
{

}

bool FD3D12Resource::InitHeapProp(D3D12_HEAP_PROPERTIES& HeapProp, D3D12_HEAP_TYPE HeapType)
{
	HeapProp.Type = HeapType;
	HeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	HeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	HeapProp.CreationNodeMask = 1;
	HeapProp.VisibleNodeMask = 1;

	return true;
}

bool FD3D12Resource::InitResourceDesc(D3D12_RESOURCE_DESC& ResourceDesc, int BufferSize)
{
	ResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	ResourceDesc.Alignment = 0;
	ResourceDesc.Width = BufferSize;
	ResourceDesc.Height = 1;
	ResourceDesc.DepthOrArraySize = 1;
	ResourceDesc.MipLevels = 1;
	ResourceDesc.Format = DXGI_FORMAT_UNKNOWN;
	ResourceDesc.SampleDesc.Count = 1;
	ResourceDesc.SampleDesc.Quality = 0;
	ResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	ResourceDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

	return true;
}
#pragma endregion

#pragma region FD3D12ResourceBarrierBatcher
void FD3D12ResourceBarrierBatcher::AddTransition(FD3D12Resource* Resource, D3D12_RESOURCE_STATES Before, D3D12_RESOURCE_STATES After)
{
	D3D12_RESOURCE_BARRIER Barrier;
	Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	Barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	Barrier.Transition.pResource = Resource->GetDxResource();
	Barrier.Transition.StateBefore = Before;
	Barrier.Transition.StateAfter = After;
	Barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	Barriers.push_back(Barrier);
}

void FD3D12ResourceBarrierBatcher::FlushIntoCommandList(FD3D12CommandList* CmdList)
{
	ID3D12GraphicsCommandList* DxCmdList = CmdList->GetDxCommandList();
	DxCmdList->ResourceBarrier(Barriers.size(), Barriers.data());
}

void FD3D12ResourceBarrierBatcher::Reset()
{
	Barriers.clear();
}
#pragma endregion
