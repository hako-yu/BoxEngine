
#pragma once

#include "D3D12Minimal.h"

class FD3D12DescriptorHeap
{
protected:
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DxHeap;
};
