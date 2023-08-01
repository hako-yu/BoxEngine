
#include "D3D12Viewport.h"

#include "D3D12Util.h"
#include "D3D12Device.h"
#include "D3D12CommandList.h"
#include "Application/PlatformApp.h"
#include "Application/WindowsApp.h"

FD3D12Viewport* FD3D12Viewport::Create(IDXGIFactory4* InDxgiFactory, FD3D12Device* InDevice, FD3D12CommandList* InCommandList)
{
	FD3D12Viewport* Viewport = new FD3D12Viewport();

	if (Viewport)
	{
		Viewport->DxScreenViewport.TopLeftX = 0;
		Viewport->DxScreenViewport.TopLeftY = 0;
		Viewport->DxScreenViewport.Width = GPlatformAppConfig.Width;
		Viewport->DxScreenViewport.Height = GPlatformAppConfig.Height;
		Viewport->DxScreenViewport.MinDepth = 0.f;
		Viewport->DxScreenViewport.MaxDepth = 1.f;

		Viewport->DxScissorRect = { 0, 0, GPlatformAppConfig.Width, GPlatformAppConfig.Height };

		Viewport->InitSwapChain(InDxgiFactory, InCommandList);
		Viewport->InitRenderTarget(InDevice->Get());
	}

	return Viewport;
}

void FD3D12Viewport::Present()
{
	ThrowIfFailed(DxgiSwapChain->Present(0, 0));
	CurrBackBufferIndex = (CurrBackBufferIndex + 1) % SwapChainBufferCount;
}

D3D12_RESOURCE_BARRIER FD3D12Viewport::BuildRenderTargetBarrier()
{
	D3D12_RESOURCE_BARRIER Barrier;
	Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	Barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	Barrier.Transition.pResource = DxBackBufferList[CurrBackBufferIndex].Get();
	Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	Barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	return Barrier;
}

D3D12_RESOURCE_BARRIER FD3D12Viewport::BuildPresentBarrier()
{
	D3D12_RESOURCE_BARRIER Barrier;
	Barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	Barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	Barrier.Transition.pResource = DxBackBufferList[CurrBackBufferIndex].Get();
	Barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	Barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	Barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

	return Barrier;
}

D3D12_CPU_DESCRIPTOR_HANDLE FD3D12Viewport::GetCurrentBackBufferDescHandle()
{
	D3D12_CPU_DESCRIPTOR_HANDLE Handle = DxRtvHeap->GetCPUDescriptorHandleForHeapStart();
	Handle.ptr += CurrBackBufferIndex * RtvDescriptorSize;
	return Handle;
}

D3D12_CPU_DESCRIPTOR_HANDLE FD3D12Viewport::GetDepthStencilDescHandle()
{
	return DxDsvHeap->GetCPUDescriptorHandleForHeapStart();
}

void FD3D12Viewport::InitRenderTarget(ID3D12Device* InDxDevice)
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = SwapChainBufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	ThrowIfFailed(InDxDevice->CreateDescriptorHeap(
		&rtvHeapDesc, IID_PPV_ARGS(&DxRtvHeap)));


	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	ThrowIfFailed(InDxDevice->CreateDescriptorHeap(
		&dsvHeapDesc, IID_PPV_ARGS(&DxDsvHeap)));

	// Create the depth/stencil buffer and view.
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = GPlatformAppConfig.Width;
	depthStencilDesc.Height = GPlatformAppConfig.Height;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;

	// Correction 11/12/2016: SSAO chapter requires an SRV to the depth buffer to read from 
	// the depth buffer.  Therefore, because we need to create two views to the same resource:
	//   1. SRV format: DXGI_FORMAT_R24_UNORM_X8_TYPELESS
	//   2. DSV Format: DXGI_FORMAT_D24_UNORM_S8_UINT
	// we need to create the depth buffer resource with a typeless format.  
	depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	D3D12_HEAP_PROPERTIES heapProperties;
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
	heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	heapProperties.CreationNodeMask = 1;
	heapProperties.VisibleNodeMask = 1;
	ThrowIfFailed(InDxDevice->CreateCommittedResource(
		&heapProperties,
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(&DxDepthStencilBuffer)));

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(DxRtvHeap->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < SwapChainBufferCount; i++)
	{
		ThrowIfFailed(DxgiSwapChain->GetBuffer(i, IID_PPV_ARGS(&DxBackBufferList[i])));
		InDxDevice->CreateRenderTargetView(DxBackBufferList[i].Get(), nullptr, rtvHeapHandle);
		RtvDescriptorSize = InDxDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		rtvHeapHandle.ptr += i * RtvDescriptorSize;
	}

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.Texture2D.MipSlice = 0;
	InDxDevice->CreateDepthStencilView(DxDepthStencilBuffer.Get(), &dsvDesc, DxDsvHeap->GetCPUDescriptorHandleForHeapStart());
}

void FD3D12Viewport::InitSwapChain(IDXGIFactory4* InDxgiFactory, FD3D12CommandList* InCommandList)
{
	// Release the previous swapchain we will be recreating.
	DxgiSwapChain.Reset();

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = GPlatformAppConfig.Width;
	sd.BufferDesc.Height = GPlatformAppConfig.Height;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.OutputWindow = hMainWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Note: Swap chain uses queue to perform flush.
	ThrowIfFailed(InDxgiFactory->CreateSwapChain(
		InCommandList->GetCmdQueue(),
		&sd,
		&DxgiSwapChain));

	ThrowIfFailed(DxgiSwapChain->ResizeBuffers(
		SwapChainBufferCount,
		GPlatformAppConfig.Width, GPlatformAppConfig.Height,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH));
}
