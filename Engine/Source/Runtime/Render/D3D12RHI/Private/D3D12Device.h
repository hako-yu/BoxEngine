
#pragma once

#include "D3D12Minimal.h"

class FD3D12Adapter;

class FD3D12Device
{
public:
	static FD3D12Device* Create(FD3D12Adapter* InAdapter);

	ID3D12Device* Get() { return DxDevice.Get(); }

protected:
	Microsoft::WRL::ComPtr<ID3D12Device> DxDevice;
};
