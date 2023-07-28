
#pragma once

#include "D3D12Device.h"
#include "WindowsD3D12Util.h"

class FWindowsD3D12Device : public FD3D12Device
{

public:
	FWindowsD3D12Device();
	~FWindowsD3D12Device();

protected:
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;

};

