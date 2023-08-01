
#pragma once

#include "D3D12Minimal.h"

class FD3D12Device;
class FD3D12CommandList;

class FD3D12Viewport
{
	friend FD3D12CommandList;

public:
	static FD3D12Viewport* Create(IDXGIFactory4* InDxgiFactory, FD3D12Device* InDevice, FD3D12CommandList* InCommandList);

	void Present();

	D3D12_RESOURCE_BARRIER BuildRenderTargetBarrier();
	D3D12_RESOURCE_BARRIER BuildPresentBarrier();

	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferDescHandle();
	D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilDescHandle();

protected:
	D3D12_VIEWPORT DxScreenViewport;
	D3D12_RECT DxScissorRect;

	static const int SwapChainBufferCount = 2;
	int CurrBackBufferIndex = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> DxBackBufferList[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> DxDepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DxRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DxDsvHeap;

	UINT RtvDescriptorSize = 0;

	Microsoft::WRL::ComPtr<IDXGISwapChain> DxgiSwapChain;

protected:
	void InitRenderTarget(ID3D12Device* InDxDevice);
	void InitSwapChain(IDXGIFactory4* InDxgiFactory, FD3D12CommandList* InCommandList);

};
