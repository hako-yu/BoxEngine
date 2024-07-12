#pragma once

#include "RHICore/RHIPass.h"
#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12PipelineState;

class FD3D12Pass : public FRHIPass, public FD3D12AdapterChild
{
public:
	FD3D12Pass(FD3D12Adapter* ParentAdapter);
	~FD3D12Pass();

public:
	void Run();

public:
	FD3D12PipelineState* GetPipelineState() { return PipelineState; }
protected:
	FD3D12PipelineState* PipelineState = nullptr;
};
