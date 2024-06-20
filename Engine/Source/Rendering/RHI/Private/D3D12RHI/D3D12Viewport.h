#pragma once

#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12Viewport : public FD3D12AdapterChild
{
public:
	FD3D12Viewport(FD3D12Adapter* ParentAdapter);
	~FD3D12Viewport();

public:
	void InitSwapChain(void* WindowHandle, int Width, int Height);

protected:
	int SizeX;
	int SizeY;

	DXGI_FORMAT BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	int BackBufferCount = 3;

	bool MsaaState = false;
	int MsaaQuality = 0;

private:
	ComPtr<IDXGISwapChain> DxSwapChain;
};
