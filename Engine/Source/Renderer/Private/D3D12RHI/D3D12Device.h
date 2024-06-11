#pragma once

#include "D3D12RHI/D3D12Common.h"

class FD3D12Device
{
private:
	ComPtr<ID3D12Device> DxDevice;
};
