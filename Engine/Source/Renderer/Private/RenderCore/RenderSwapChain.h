#pragma once

#include <wrl.h>
#include <dxgi.h>
#include <d3d12.h>

using namespace Microsoft::WRL;

class FRenderDevice;
class FRenderCommandList;

class FRenderSwapChain
{
public:
	void Init(FRenderDevice* RenderDevice, FRenderCommandList* RenderCommandList);
	void Setup(void* WindowHandle, int Width, int Height);

private:
	static const int SwapChainBufferCount = 3;
	DXGI_FORMAT SwapChainBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;

	bool MsaaState = false;
	int MsaaQuality = 0;

	ComPtr<IDXGISwapChain> DxSwapChain;

private:
	IDXGIFactory* DxFactory = nullptr;
	ID3D12CommandQueue* DxCommandQueue = nullptr;
};
