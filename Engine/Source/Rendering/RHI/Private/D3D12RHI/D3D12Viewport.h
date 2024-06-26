#pragma once

#include "CoreMinimal.h"
#include "D3D12RHI/D3D12RHICommon.h"

class FD3D12Resource;

class FD3D12Viewport : public FD3D12AdapterChild
{
public:
	FD3D12Viewport(FD3D12Adapter* ParentAdapter);
	~FD3D12Viewport();

public:
	void InitSwapChain(void* WindowHandle, int Width, int Height);
	void Resize(int Width, int Height);

	FD3D12Resource* GetCurrentFrontBuffer() { return FrontBuffers[CurFrontBufferIndex]; }
	FD3D12Resource* GetCurrentBackBuffer() { return BackBuffers[CurBackBufferIndex]; }

	void Present();

protected:
	void OnBufferRefresh();
	void ClearBuffer();
	void InitFrontBuffers();
	void InitBackBuffers();

protected:
	int SizeX;
	int SizeY;

	DXGI_FORMAT BufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	int FrontBufferCount = 2;
	int BackBufferCount = 2;
	int CurFrontBufferIndex = 0;
	int CurBackBufferIndex = 0;

	bool MsaaState = false;
	int MsaaQuality = 0;

protected:
	TArray<FD3D12Resource*> FrontBuffers;
	TArray<FD3D12Resource*> BackBuffers;

private:
	ComPtr<IDXGISwapChain> DxSwapChain;
};
