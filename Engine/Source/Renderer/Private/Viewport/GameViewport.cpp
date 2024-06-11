#include "Viewport/GameViewport.h"

#include <windows.h>

#include "Logging.h"
#include "RenderCore/RenderCore.h"
#include "RenderCore/RenderSwapChain.h"
#include "RenderCore/RenderCommandList.h"

/* ====================================================================
 * WIN API
 * ==================================================================== */
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_ACTIVATE:
        BOX_LOG("WM_ACTIVATE");
        return 0;
    case WM_DESTROY:
        BOX_LOG("WM_DESTROY");
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


/* ====================================================================
 * FGameViewport
 * ==================================================================== */
FGameViewport::FGameViewport()
    : Wnd(nullptr)
    , RenderSwapChain(nullptr)
    , Width(0)
    , Height(0)
{ }

FGameViewport::~FGameViewport()
{
    if (Wnd)
    {
        CloseWindow((HWND)Wnd);
        DestroyWindow((HWND)Wnd);
    }
}

bool FGameViewport::CreateViewport(void* AppInstance, int Width, int Height)
{
    this->Width = Width;
    this->Height = Height;

    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = (HINSTANCE)AppInstance;
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = "MainWnd";

    if (!RegisterClass(&wc))
    {
        MessageBox(0, "RegisterClass Failed.", 0, 0);
        return false;
    }

    Wnd = CreateWindow(
        "MainWnd",
        "BoxEngine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        Width,
        Height,
        0,
        0,
        (HINSTANCE)AppInstance,
        0);

    if (!Wnd)
    {
        MessageBox(0, "CreateWindow Failed.", 0, 0);
        return false;
    }

    ShowWindow((HWND)Wnd, SW_SHOW);
    UpdateWindow((HWND)Wnd);

    FRenderCore* RenderCore = FRenderCore::Get();
    RenderSwapChain = RenderCore->CreateSwapChain();
    RenderSwapChain->Setup(Wnd, Width, Height);
}

void FGameViewport::ApplyViewport(FRenderCommandList* CommandList)
{
    ID3D12GraphicsCommandList* DxCommandList = CommandList->GetDxCommandList();

    D3D12_VIEWPORT ScreenViewport;
    ScreenViewport.TopLeftX = 0;
    ScreenViewport.TopLeftY = 0;
    ScreenViewport.Width = static_cast<float>(Width);
    ScreenViewport.Height = static_cast<float>(Height);
    ScreenViewport.MinDepth = 0.0f;
    ScreenViewport.MaxDepth = 1.0f;

    D3D12_RECT ScissorRect;
    ScissorRect = { 0, 0, Width, Height };

    DxCommandList->RSSetViewports(1, &ScreenViewport);
    DxCommandList->RSSetScissorRects(1, &ScissorRect);
}
