#include "D3D12RHI/D3D12Viewport.h"

#include "D3D12RHI/D3D12Adapter.h"
#include "D3D12RHI/D3D12Device.h"
#include "D3D12RHI/D3D12CommandList.h"
#include "D3D12RHI/D3D12Resources.h"

FD3D12Viewport::FD3D12Viewport(FD3D12Adapter* ParentAdapter)
	: FD3D12AdapterChild(ParentAdapter)
	, SizeX(1024)
	, SizeY(768)
{
    
}

FD3D12Viewport::~FD3D12Viewport()
{

}

void FD3D12Viewport::InitSwapChain(void* WindowHandle, int Width, int Height)
{
    DxSwapChain.Reset();

    SizeX = Width;
    SizeY = Height;
    
    IDXGIFactory* DxFactory = ParentAdapter->GetDxFactory();
    ID3D12CommandQueue* DxCommandQueue = ParentAdapter->GetRootDevice()->GetRootQueue()->GetDxCommandQueue();

    DXGI_SWAP_CHAIN_DESC SwapChainDesc;
    SwapChainDesc.BufferDesc.Width = SizeX;
    SwapChainDesc.BufferDesc.Height = SizeY;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDesc.BufferDesc.Format = BufferFormat;
    SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    SwapChainDesc.SampleDesc.Count = MsaaState ? 4 : 1;
    SwapChainDesc.SampleDesc.Quality = MsaaState ? (MsaaQuality - 1) : 0;
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = FrontBufferCount;
    SwapChainDesc.OutputWindow = (HWND)WindowHandle;
    SwapChainDesc.Windowed = true;
    SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    HRESULT HRes;
    HRes = DxFactory->CreateSwapChain(
        DxCommandQueue,
        &SwapChainDesc,
        &DxSwapChain);
    ThrowIfFailed(HRes);

    OnBufferRefresh();
}

void FD3D12Viewport::Resize(int Width, int Height)
{
    SizeX = Width;
    SizeY = Height;

    HRESULT HRes;
    HRes = DxSwapChain->ResizeBuffers(
        FrontBufferCount,
        SizeX, SizeY,
        BufferFormat,
        DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
    ThrowIfFailed(HRes);

    OnBufferRefresh();
}

void FD3D12Viewport::Present()
{
    FD3D12CommandList* CmdList = ParentAdapter->GetRootDevice()->GetDefaultCommandList();

    FD3D12Resource* FrontBuffer = GetCurrentFrontBuffer();
    FD3D12Resource* BackBuffer = GetCurrentBackBuffer();

    FD3D12ResourceBarrierBatcher BarrierBatcher;
    BarrierBatcher.AddTransition(FrontBuffer, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_COPY_DEST);
    BarrierBatcher.AddTransition(BackBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_COPY_SOURCE);
    BarrierBatcher.FlushIntoCommandList(CmdList);
    
    ID3D12GraphicsCommandList* DxCmdList = CmdList->GetDxCommandList();
    DxCmdList->CopyResource(FrontBuffer->GetDxResource(), BackBuffer->GetDxResource());

    BarrierBatcher.Reset();
    BarrierBatcher.AddTransition(FrontBuffer, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PRESENT);
    BarrierBatcher.AddTransition(BackBuffer, D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_RENDER_TARGET);
    BarrierBatcher.FlushIntoCommandList(CmdList);

    FD3D12CommandQueue* CmdQueue = ParentAdapter->GetRootDevice()->GetRootQueue();
    CmdQueue->ExecuteCommandList(CmdList);

    DxSwapChain->Present(0, 0);

    CurFrontBufferIndex = (CurFrontBufferIndex + 1) % FrontBufferCount;
    CurBackBufferIndex = (CurBackBufferIndex + 1) % BackBufferCount;
}

void FD3D12Viewport::OnBufferRefresh()
{
    FD3D12Device* Device = ParentAdapter->GetRootDevice();

    CurFrontBufferIndex = 0;
    CurBackBufferIndex = 0;

    ClearBuffer();

    InitFrontBuffers();
    InitBackBuffers();
}

void FD3D12Viewport::ClearBuffer()
{
    for (FD3D12Resource* Resource : FrontBuffers) delete Resource;
    FrontBuffers.clear();

    for (FD3D12Resource* Resource : BackBuffers) delete Resource;
    BackBuffers.clear();
}

void FD3D12Viewport::InitFrontBuffers()
{
    for (int i = 0; i < FrontBufferCount; i++)
    {
        ID3D12Resource* DxResource;
        DxSwapChain->GetBuffer(i, IID_PPV_ARGS(&DxResource));
        FrontBuffers.push_back(new FD3D12Resource(ParentAdapter->GetRootDevice(), DxResource));
    }
}

void FD3D12Viewport::InitBackBuffers()
{
    D3D12_HEAP_PROPERTIES HeapProp;
    HeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
    HeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    HeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    HeapProp.CreationNodeMask = 1;
    HeapProp.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC ResDesc;
    ResDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    ResDesc.Alignment = 0;
    ResDesc.Width = SizeX;
    ResDesc.Height = SizeY;
    ResDesc.DepthOrArraySize = 1;
    ResDesc.MipLevels = 1;
    ResDesc.Format = BufferFormat;
    ResDesc.SampleDesc.Count = MsaaState ? 4 : 1;
    ResDesc.SampleDesc.Quality = MsaaState ? (MsaaQuality - 1) : 0;
    ResDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    ResDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;

    D3D12_CLEAR_VALUE ClearValue;
    ClearValue.Format = BufferFormat;

    for (int i = 0; i < BackBufferCount; i++)
    {
        FD3D12Resource* Resource = new FD3D12Resource(
            ParentAdapter->GetRootDevice(),
            &HeapProp,
            &ResDesc,
            D3D12_RESOURCE_STATE_RENDER_TARGET,
            &ClearValue);
        BackBuffers.push_back(Resource);
    }
}
