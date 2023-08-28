
#pragma once

#include "CoreMinimal.h"
#include "RHIViewport.h"
#include "D3D12ThirdParty.h"

class FD3D12Adapter;
class FD3D12Resource;
class FD3D12DescriptorHeap;

class FD3D12Viewport : public FRHIViewport
{
public:
	FD3D12Viewport(FD3D12Adapter* InAdapter, HWND WindowHandle, uint32 SizeX, uint32 SizeY);
	~FD3D12Viewport();

public:
	void Init();

private:
	void InitSwapChain();
	void InitBackBuffers();

private:
	FD3D12Adapter* Adapter;
	HWND WindowHandle;

private:
	uint32 BackBufferCount = 2;
	TArray<FD3D12Resource*> BackBufferList;

	FD3D12DescriptorHeap* BackBufferDescHeap;

	Microsoft::WRL::ComPtr<IDXGISwapChain> DxSwapChain;
};
