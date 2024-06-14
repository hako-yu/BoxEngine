#pragma once

#include "RHICore/RHIViewport.h"
#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12Viewport : public FRHIViewport, public FD3D12AdapterChild
{
public:
	FD3D12Viewport(FD3D12Adapter* ParentAdapter);
	~FD3D12Viewport();

public:
	void InitSwapChain();

protected:
	int SizeX;
	int SizeY;

private:
	ComPtr<IDXGISwapChain> DxSwapChain;
};
