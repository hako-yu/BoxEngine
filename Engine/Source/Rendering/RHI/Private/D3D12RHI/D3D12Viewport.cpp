#include "D3D12RHI/D3D12Viewport.h"

#include "D3D12RHI/D3D12Adapter.h"
#include "D3D12RHI/D3D12Device.h"
#include "D3D12RHI/D3D12CommandList.h"

FD3D12Viewport::FD3D12Viewport(FD3D12Adapter* ParentAdapter)
	: FD3D12AdapterChild(ParentAdapter)
	, SizeX(1024)
	, SizeY(768)
{
    
}

FD3D12Viewport::~FD3D12Viewport()
{

}

void FD3D12Viewport::InitSwapChain()
{
    IDXGIFactory* DxFactory = ParentAdapter->GetDxFactory();
    ID3D12CommandQueue* DxCommandQueue = ParentAdapter->GetRootDevice()->GetRootQueue()->GetDxCommandQueue();

    DXGI_SWAP_CHAIN_DESC SwapChainDesc;
    /*
    SwapChainDesc.BufferDesc.Width = mClientWidth;
    SwapChainDesc.BufferDesc.Height = mClientHeight;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDesc.BufferDesc.Format = mBackBufferFormat;
    SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    SwapChainDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
    SwapChainDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = SwapChainBufferCount;
    SwapChainDesc.OutputWindow = mhMainWnd;
    SwapChainDesc.Windowed = true;
    SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    */

    HRESULT HRes;
    HRes = DxFactory->CreateSwapChain(
        DxCommandQueue,
        &SwapChainDesc,
        &DxSwapChain);
    ThrowIfFailed(HRes);
}
