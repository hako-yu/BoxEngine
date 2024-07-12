#pragma once

#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12PipelineState : public FD3D12DeviceChild
{
public:
	FD3D12PipelineState(FD3D12Device* ParentDevice);
	~FD3D12PipelineState();

public:
	void BuildPipelineStateObject();


public:
	ID3D12PipelineState* GetDxPipelineState() { return DxPipelineState.Get(); }
private:
	ComPtr<ID3D12PipelineState> DxPipelineState;
};
