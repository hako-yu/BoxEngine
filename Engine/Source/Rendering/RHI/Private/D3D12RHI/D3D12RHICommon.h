#pragma once

#include "D3D12RHI/D3D12Util.h"

class FD3D12Adapter;
class FD3D12Device;

class FD3D12AdapterChild
{
public:
	FD3D12AdapterChild(FD3D12Adapter* Parent)
		: ParentAdapter(Parent)
	{}

	FD3D12Adapter* GetParentAdapter() { return ParentAdapter; }

protected:
	FD3D12Adapter* ParentAdapter;
};

class FD3D12DeviceChild
{
public:
	FD3D12DeviceChild(FD3D12Device* Parent)
		: ParentDevice(Parent)
	{}

	FD3D12Device* GetParentDevice() { return ParentDevice; }

protected:
	FD3D12Device* ParentDevice;
};
