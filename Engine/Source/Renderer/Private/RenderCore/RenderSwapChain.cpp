#include "RenderCore/RenderSwapChain.h"

#include "RenderCore/RenderDevice.h"
#include "RenderCore/RenderCommandList.h"

void FRenderSwapChain::Init(FRenderDevice* RenderDevice, FRenderCommandList* RenderCommandList)
{
    DxFactory = RenderDevice->GetDxFactory();
    DxCommandQueue = RenderCommandList->GetDxCommandQueue();
}

void FRenderSwapChain::Setup(void* WindowHandle, int Width, int Height)
{
    DXGI_SWAP_CHAIN_DESC SwapChainDesc;
    SwapChainDesc.BufferDesc.Width = Width;
    SwapChainDesc.BufferDesc.Height = Height;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDesc.BufferDesc.Format = SwapChainBufferFormat;
    SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    SwapChainDesc.SampleDesc.Count = MsaaState ? 4 : 1;
    SwapChainDesc.SampleDesc.Quality = MsaaState ? (MsaaQuality - 1) : 0;
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = SwapChainBufferCount;
    SwapChainDesc.OutputWindow = (HWND)WindowHandle;
    SwapChainDesc.Windowed = true;
    SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    // Note: Swap chain uses queue to perform flush.
    DxFactory->CreateSwapChain(DxCommandQueue, &SwapChainDesc, &DxSwapChain);
}
