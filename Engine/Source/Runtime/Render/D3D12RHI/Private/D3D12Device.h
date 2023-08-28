
#pragma once

#include "D3D12Utils.h"

class FD3D12Adapter;
class FD3D12CommandQueue;

class FD3D12Device
{
public:
	FD3D12Device(FD3D12Adapter* Adapter);
	~FD3D12Device();

public:
	inline ID3D12Device* GetDxDevice() const { return DxDevice.Get(); }
	inline FD3D12CommandQueue* GetCommandQueue() const { return CommandQueue; }

	void Setup();

private:
	FD3D12CommandQueue* CommandQueue;

	Microsoft::WRL::ComPtr<ID3D12Device> DxDevice;
};
