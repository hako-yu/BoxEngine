#pragma once

#include "Types.h"
#include <memory>

#ifdef PLATFORM_WINDOWS
#include "Windows/Window.h"
#endif

class FLauncher
{
public:
    FLauncher();
    ~FLauncher();
    
    // 初始化和清理
    bool Initialize();
    void Shutdown();
    
    // 主循环
    void Run();
    
    // 窗口事件回调
    void OnWindowResize(FInt32 NewWidth, FInt32 NewHeight);
    void OnWindowClose();

private:
    bool bInitialized;
    
#ifdef PLATFORM_WINDOWS
    FUniquePtr<FWindow> MainWindow;
#endif
}; 