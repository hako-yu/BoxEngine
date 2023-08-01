
#include "D3D12Core.h"

#include "Application/PlatformApp.h"
#include "Application/WindowsApp.h"

#include <DirectXColors.h>
#include "D3D12Util.h"

#include "D3D12Adapter.h"
#include "D3D12Device.h"
#include "D3D12CommandList.h"

FD3D12Core* FD3D12Core::Create()
{
	FD3D12Core* Core = new FD3D12Core();
	return Core;
}

void FD3D12Core::InitAdapters()
{
	IDXGIAdapter* TmpAdapter;
	for (UINT i = 0; DxgiFactory->EnumAdapters(i, &TmpAdapter) != DXGI_ERROR_NOT_FOUND; i++)
	{
		AdapterList.Add(FD3D12Adapter::Create(TmpAdapter));
	}
}

void FD3D12Core::InitDevice()
{
	Device = FD3D12Device::Create(AdapterList.Num() > 0 ? AdapterList[0] : nullptr);
}

void FD3D12Core::CheckSupports()
{
	
}

void FD3D12Core::InitCommandList()
{
	CommandList = FD3D12CommandList::Create(Device);
}

void FD3D12Core::InitSwapChain()
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
	ThrowIfFailed(DxgiFactory->CreateSwapChain(
		CommandList->GetCmdQueue(),
		&sd,
		&DxgiSwapChain));
}

void FD3D12Core::Init()
{
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&DxgiFactory)));

	InitAdapters();
	InitDevice();
	InitCommandList();
	InitSwapChain();
}

void FD3D12Core::Draw()
{
	CommandList->Reset();
	CommandList->Execute();

	ThrowIfFailed(DxgiSwapChain->Present(0, 0));
}

void FD3D12Core::Release()
{
	for (FD3D12Adapter* Adapter : AdapterList)
	{
		delete Adapter;
	}
	AdapterList.clear();

	if (CommandList)
	{
		CommandList->Release();
		delete CommandList;
	}
}
