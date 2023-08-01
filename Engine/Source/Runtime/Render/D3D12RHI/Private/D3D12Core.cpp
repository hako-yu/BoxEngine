
#include "D3D12Core.h"

#include "Application/PlatformApp.h"
#include "Application/WindowsApp.h"

#include <DirectXColors.h>
#include "D3D12Util.h"

#include "D3D12Adapter.h"
#include "D3D12Device.h"
#include "D3D12CommandList.h"
#include "D3D12Viewport.h"

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

void FD3D12Core::InitViewport()
{
	MainViewport = FD3D12Viewport::Create(DxgiFactory.Get(), Device, CommandList);
}

void FD3D12Core::Init()
{
	Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
	ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
	debugController->EnableDebugLayer();

	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&DxgiFactory)));

	InitAdapters();
	InitDevice();
	InitCommandList();
	InitViewport();
}

void FD3D12Core::Draw()
{
	CommandList->Reset();
	CommandList->SetViewport(MainViewport);
	CommandList->Execute();
}

void FD3D12Core::Release()
{
	for (FD3D12Adapter* Adapter : AdapterList)
	{
		delete Adapter;
	}
	AdapterList.clear();

	if (Device)
	{
		delete Device;
	}

	if (CommandList)
	{
		CommandList->Release();
		delete CommandList;
	}
}
