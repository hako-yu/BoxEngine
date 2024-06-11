#pragma once

#include "D3D12RHI/D3D12Common.h"

class FD3D12SViewport
{
private:
	bool MsaaState = false;
	int MsaaQuality = 0;

	static const int SwapChainBufferCount = 3;
	DXGI_FORMAT SwapChainBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];


private:
	ComPtr<IDXGISwapChain> DxSwapChain;
};
