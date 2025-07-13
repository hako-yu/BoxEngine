#include "Launcher.h"
#include "Logging/LogManager.h"
#include <cassert>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 设置控制台输出（用于调试）
#ifdef _DEBUG
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif
    
    // 创建启动器实例
    FLauncher Launcher;
    
    // 初始化引擎
    if (!Launcher.Initialize())
    {
        MessageBoxA(nullptr, "Failed to initialize BoxEngine", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }
    
    // 运行主循环
    Launcher.Run();
    
    // 清理资源
    Launcher.Shutdown();
    
    return 0;
}

#else
// 非Windows平台的占位实现
int main(int argc, char* argv[])
{
    // 这里可以为其他平台实现主入口
    return 0;
}
#endif 