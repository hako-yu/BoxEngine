#pragma once

#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12Pass : public FD3D12AdapterChild
{
public:
	FD3D12Pass(FD3D12Adapter* ParentAdapter);
	~FD3D12Pass();

public:
	void Run();
};
