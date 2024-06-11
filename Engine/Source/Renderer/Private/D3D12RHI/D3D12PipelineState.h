#pragma once

#include "D3D12RHI/D3D12Common.h"

class FD3D12CommandList;

class FD3D12PipelineState
{
public:
	void FlushIntoCommandList(FD3D12CommandList* CommandList);
};
