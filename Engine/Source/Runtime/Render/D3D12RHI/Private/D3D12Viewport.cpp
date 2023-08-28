
#include "D3D12Viewport.h"

#include "D3D12Adapter.h"
#include "D3D12Device.h"
#include "D3D12CommandQueue.h"
#include "D3D12Descriptor.h"
#include "D3D12Resource.h"

FD3D12Viewport::FD3D12Viewport(FD3D12Adapter* InAdapter, HWND WindowHandle, uint32 SizeX, uint32 SizeY)
	: FRHIViewport(SizeX, SizeY)
	, Adapter(InAdapter)
	, WindowHandle(WindowHandle)
{
	BackBufferDescHeap = nullptr;
}

FD3D12Viewport::~FD3D12Viewport()
{

}

void FD3D12Viewport::Init()
{
	InitSwapChain();
	InitBackBuffers();
}

void FD3D12Viewport::InitSwapChain()
{
	IDXGIFactory2* DxgiFactory = Adapter->DxgiFactory;
	ID3D12CommandQueue* DxCommandQueue = Adapter->GetDevice()->GetCommandQueue()->GetDxCommandQueue();

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	SwapChainDesc.BufferDesc.Width = SizeX;
	SwapChainDesc.BufferDesc.Height = SizeY;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.OutputWindow = WindowHandle;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ThrowIfFailed(DxgiFactory->CreateSwapChain(
		DxCommandQueue,
		&SwapChainDesc,
		&DxSwapChain));
}

void FD3D12Viewport::InitBackBuffers()
{
	FD3D12Device* Device = Adapter->GetDevice();
	ID3D12Device* DxDevice = Device->GetDxDevice();

	for (uint32 i = 0; i < BackBufferCount; i++)
	{
		BackBufferList.Add(new FD3D12Resource());
	}

	BackBufferDescHeap = new FD3D12DescriptorHeap(Device, BackBufferCount, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, D3D12_DESCRIPTOR_HEAP_FLAG_NONE);

	for (uint32 i = 0; i < BackBufferCount; i++)
	{
		ID3D12Resource* DxBackBuffer = BackBufferList[i]->GetDxResource();
		ThrowIfFailed(DxSwapChain->GetBuffer(i, IID_PPV_ARGS(&DxBackBuffer)));
		DxDevice->CreateRenderTargetView(DxBackBuffer, nullptr, BackBufferDescHeap->GetCpuSlotHandle(i));
	}
}
