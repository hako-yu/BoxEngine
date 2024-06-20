#include "Viewport/Viewport.h"

#include <windows.h>

#include "Logging.h"
#include "RHICore/RHICommands.h"

FViewport::FViewport(int InWidth, int InHeight)
	: Width(InWidth)
	, Height(InHeight)
	, Wnd(nullptr)
	, AppInstance(nullptr)
{

}

FViewport::~FViewport()
{
    if (Wnd)
    {
        CloseWindow((HWND)Wnd);
        DestroyWindow((HWND)Wnd);
    }
}

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

void FViewport::AddToWindow(void* InAppInstance)
{
	AppInstance = InAppInstance;

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
        return;
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
        return;
    }

    ShowWindow((HWND)Wnd, SW_SHOW);
    // UpdateWindow((HWND)Wnd);

    EXECUTE_RHI_COMMAND(ResetOutputWindow)(Wnd, Width, Height);
}

void FViewport::Update()
{
    UpdateWindow((HWND)Wnd);
}
