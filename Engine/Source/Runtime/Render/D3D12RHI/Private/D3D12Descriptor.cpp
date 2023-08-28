
#include "D3D12Descriptor.h"
#include "D3D12Device.h"

FD3D12DescriptorHeap::FD3D12DescriptorHeap(FD3D12Device* InDevice, uint32 InNumDesc, D3D12_DESCRIPTOR_HEAP_TYPE InType, D3D12_DESCRIPTOR_HEAP_FLAGS InFlags, uint32 InNodeMask)
	: NumDesc(InNumDesc)
	, Type(InType)
	, Flags(InFlags)
	, NodeMask(InNodeMask)
{
	ID3D12Device* DxDevice = InDevice->GetDxDevice();

	D3D12_DESCRIPTOR_HEAP_DESC HeapDesc;
	HeapDesc.NumDescriptors = NumDesc;
	HeapDesc.Type = Type;
	HeapDesc.Flags = Flags;
	HeapDesc.NodeMask = NodeMask;
	ThrowIfFailed(DxDevice->CreateDescriptorHeap(
		&HeapDesc, IID_PPV_ARGS(&DxDescriptorHeap)));

	DescSize = DxDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	CpuBase = DxDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	GpuBase = DxDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
}

FD3D12DescriptorHeap::~FD3D12DescriptorHeap()
{

}

D3D12_CPU_DESCRIPTOR_HANDLE FD3D12DescriptorHeap::GetCpuSlotHandle(uint32 Slot)
{
	D3D12_CPU_DESCRIPTOR_HANDLE Result(CpuBase);
	Result.ptr += Slot * DescSize;
	return Result;
}
