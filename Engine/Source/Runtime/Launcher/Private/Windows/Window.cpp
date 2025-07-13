#include "Windows/Window.h"
#include "Logging/LogManager.h"
#include <cassert>

#ifdef PLATFORM_WINDOWS

// 静态成员初始化
FInt32 FWindow::WindowClassRefCount = 0;
const FChar* FWindow::WindowClassName = "BoxEngineWindow";

FWindow::FWindow()
    : WindowHandle(nullptr)
    , Width(0)
    , Height(0)
    , bShouldClose(false)
    , ResizeCallback(nullptr)
    , CloseCallback(nullptr)
{
    RegisterWindowClass();
}

FWindow::~FWindow()
{
    Destroy();
    UnregisterWindowClass();
}

bool FWindow::Create(const FChar* InTitle, FInt32 InWidth, FInt32 InHeight)
{
    assert(InTitle != nullptr);
    assert(InWidth > 0 && InHeight > 0);
    
    Title = InTitle;
    Width = InWidth;
    Height = InHeight;
    
    // 计算窗口大小（包含标题栏和边框）
    RECT WindowRect = { 0, 0, Width, Height };
    AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE);
    
    FInt32 ActualWidth = WindowRect.right - WindowRect.left;
    FInt32 ActualHeight = WindowRect.bottom - WindowRect.top;
    
    // 创建窗口
    WindowHandle = CreateWindowEx(
        0,                              // 扩展样式
        WindowClassName,                // 窗口类名
        Title.c_str(),                 // 窗口标题
        WS_OVERLAPPEDWINDOW,          // 窗口样式
        CW_USEDEFAULT,                 // X位置
        CW_USEDEFAULT,                 // Y位置
        ActualWidth,                   // 宽度
        ActualHeight,                  // 高度
        nullptr,                       // 父窗口
        nullptr,                       // 菜单
        GetModuleHandle(nullptr),      // 实例句柄
        this                          // 用户数据
    );
    
    if (!WindowHandle)
    {
        LOG_ERROR("Failed to create window");
        return false;
    }
    
    // 设置窗口用户数据
    SetWindowLongPtr(WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    
    LOG_INFO("Window created successfully: " + Title);
    return true;
}

void FWindow::Destroy()
{
    if (WindowHandle)
    {
        DestroyWindow(WindowHandle);
        WindowHandle = nullptr;
        LOG_INFO("Window destroyed: " + Title);
    }
}

void FWindow::ProcessMessages()
{
    MSG Message;
    while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE))
    {
        if (Message.message == WM_QUIT)
        {
            bShouldClose = true;
            break;
        }
        
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
}

bool FWindow::ShouldClose() const
{
    return bShouldClose;
}

bool FWindow::IsMinimized() const
{
    return WindowHandle && IsIconic(WindowHandle);
}

bool FWindow::IsMaximized() const
{
    return WindowHandle && IsZoomed(WindowHandle);
}

bool FWindow::IsVisible() const
{
    return WindowHandle && IsWindowVisible(WindowHandle);
}

void FWindow::Show()
{
    if (WindowHandle)
    {
        ShowWindow(WindowHandle, SW_SHOW);
    }
}

void FWindow::Hide()
{
    if (WindowHandle)
    {
        ShowWindow(WindowHandle, SW_HIDE);
    }
}

void FWindow::Minimize()
{
    if (WindowHandle)
    {
        ShowWindow(WindowHandle, SW_MINIMIZE);
    }
}

void FWindow::Maximize()
{
    if (WindowHandle)
    {
        ShowWindow(WindowHandle, SW_MAXIMIZE);
    }
}

void FWindow::Restore()
{
    if (WindowHandle)
    {
        ShowWindow(WindowHandle, SW_RESTORE);
    }
}

LRESULT CALLBACK FWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    FWindow* Window = GetWindowFromHandle(hWnd);
    
    switch (uMsg)
    {
    case WM_CREATE:
        {
            CREATESTRUCT* CreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            Window = reinterpret_cast<FWindow*>(CreateStruct->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(Window));
        }
        break;
        
    case WM_DESTROY:
        if (Window)
        {
            Window->bShouldClose = true;
            if (Window->CloseCallback)
            {
                Window->CloseCallback();
            }
        }
        PostQuitMessage(0);
        break;
        
    case WM_SIZE:
        if (Window)
        {
            FInt32 NewWidth = LOWORD(lParam);
            FInt32 NewHeight = HIWORD(lParam);
            
            Window->Width = NewWidth;
            Window->Height = NewHeight;
            
            if (Window->ResizeCallback)
            {
                Window->ResizeCallback(NewWidth, NewHeight);
            }
        }
        break;
        
    case WM_CLOSE:
        if (Window)
        {
            Window->bShouldClose = true;
            if (Window->CloseCallback)
            {
                Window->CloseCallback();
            }
        }
        break;
        
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    
    return 0;
}

FWindow* FWindow::GetWindowFromHandle(HWND hWnd)
{
    return reinterpret_cast<FWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}

void FWindow::RegisterWindowClass()
{
    if (WindowClassRefCount++ == 0)
    {
        WNDCLASSEX WindowClass = {};
        WindowClass.cbSize = sizeof(WNDCLASSEX);
        WindowClass.style = CS_HREDRAW | CS_VREDRAW;
        WindowClass.lpfnWndProc = WindowProc;
        WindowClass.hInstance = GetModuleHandle(nullptr);
        WindowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
        WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        WindowClass.lpszClassName = WindowClassName;
        
        if (!RegisterClassEx(&WindowClass))
        {
            LOG_ERROR("Failed to register window class");
        }
    }
}

void FWindow::UnregisterWindowClass()
{
    if (--WindowClassRefCount == 0)
    {
        UnregisterClass(WindowClassName, GetModuleHandle(nullptr));
    }
}

#endif // PLATFORM_WINDOWS 