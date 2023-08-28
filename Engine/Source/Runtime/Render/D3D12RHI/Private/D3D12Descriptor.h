
#pragma once

#include "CoreMinimal.h"
#include "D3D12Utils.h"

class FD3D12Device;

class FD3D12DescriptorHeap
{
public:
	FD3D12DescriptorHeap(FD3D12Device* InDevice, uint32 InNumDesc, D3D12_DESCRIPTOR_HEAP_TYPE InType, D3D12_DESCRIPTOR_HEAP_FLAGS InFlags, uint32 InNodeMask = 0);
	~FD3D12DescriptorHeap();

public:
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuSlotHandle(uint32 Slot);

private:
	const uint32 NumDesc;
	const D3D12_DESCRIPTOR_HEAP_TYPE Type;
	const D3D12_DESCRIPTOR_HEAP_FLAGS Flags;
	const uint32 NodeMask;

	uint32 DescSize;
	D3D12_CPU_DESCRIPTOR_HANDLE CpuBase;
	D3D12_GPU_DESCRIPTOR_HANDLE GpuBase;

private:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DxDescriptorHeap;
};
