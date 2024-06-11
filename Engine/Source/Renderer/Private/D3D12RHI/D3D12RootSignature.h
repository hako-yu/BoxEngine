#pragma once

#include "D3D12RHI/D3D12Common.h"

class FD3D12RootSignature
{
private:
	ComPtr<ID3D12RootSignature> DxRootSignature;
};
