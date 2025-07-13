#pragma once

#include "Types.h"
#include <memory>
#include <functional>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>

class FWindow
{
public:
    FWindow();
    virtual ~FWindow();
    
    // 窗口创建和销毁
    bool Create(const FChar* Title, FInt32 Width, FInt32 Height);
    void Destroy();
    
    // 窗口消息处理
    void ProcessMessages();
    bool ShouldClose() const;
    
    // 窗口属性
    FWindowHandle GetHandle() const { return WindowHandle; }
    FInt32 GetWidth() const { return Width; }
    FInt32 GetHeight() const { return Height; }
    const FString& GetTitle() const { return Title; }
    
    // 窗口状态
    bool IsMinimized() const;
    bool IsMaximized() const;
    bool IsVisible() const;
    
    // 窗口操作
    void Show();
    void Hide();
    void Minimize();
    void Maximize();
    void Restore();
    
    // 事件回调
    using FWindowResizeCallback = std::function<void(FInt32, FInt32)>;
    using FWindowCloseCallback = std::function<void()>;
    
    void SetResizeCallback(FWindowResizeCallback Callback) { ResizeCallback = Callback; }
    void SetCloseCallback(FWindowCloseCallback Callback) { CloseCallback = Callback; }

private:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    
    HWND WindowHandle;
    FString Title;
    FInt32 Width;
    FInt32 Height;
    bool bShouldClose;
    
    FWindowResizeCallback ResizeCallback;
    FWindowCloseCallback CloseCallback;
    
    static FWindow* GetWindowFromHandle(HWND hWnd);
    static void RegisterWindowClass();
    static void UnregisterWindowClass();
    
    static FInt32 WindowClassRefCount;
    static const FChar* WindowClassName;
};

#endif // PLATFORM_WINDOWS 