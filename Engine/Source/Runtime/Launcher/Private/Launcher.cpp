#include "Launcher.h"
#include "Logging/LogManager.h"
#include <cassert>

#ifdef PLATFORM_WINDOWS
#include "Windows/Window.h"
#endif

FLauncher::FLauncher()
    : bInitialized(false)
{
}

FLauncher::~FLauncher()
{
    Shutdown();
}

bool FLauncher::Initialize()
{
    if (bInitialized)
    {
        LOG_WARNING("Launcher already initialized");
        return true;
    }
    
    LOG_INFO("Initializing BoxEngine Launcher...");
    
    // 初始化日志系统
    FLogManager::GetInstance().Initialize();
    
    // 创建主窗口
#ifdef PLATFORM_WINDOWS
    MainWindow = std::make_unique<FWindow>();
    
    if (!MainWindow->Create("BoxEngine", EngineConstants::DefaultWindowWidth, EngineConstants::DefaultWindowHeight))
    {
        LOG_ERROR("Failed to create main window");
        return false;
    }
    
    // 设置窗口回调
    MainWindow->SetResizeCallback([this](FInt32 NewWidth, FInt32 NewHeight) {
        this->OnWindowResize(NewWidth, NewHeight);
    });
    
    MainWindow->SetCloseCallback([this]() {
        this->OnWindowClose();
    });
    
    MainWindow->Show();
#endif
    
    bInitialized = true;
    LOG_INFO("BoxEngine Launcher initialized successfully");
    return true;
}

void FLauncher::Shutdown()
{
    if (!bInitialized)
    {
        return;
    }
    
    LOG_INFO("Shutting down BoxEngine Launcher...");
    
#ifdef PLATFORM_WINDOWS
    if (MainWindow)
    {
        MainWindow->Destroy();
        MainWindow.reset();
    }
#endif
    
    // 关闭日志系统
    FLogManager::GetInstance().Shutdown();
    
    bInitialized = false;
    LOG_INFO("BoxEngine Launcher shutdown complete");
}

void FLauncher::Run()
{
    if (!bInitialized)
    {
        LOG_ERROR("Launcher not initialized");
        return;
    }
    
    LOG_INFO("Starting BoxEngine main loop...");
    
#ifdef PLATFORM_WINDOWS
    // 主消息循环
    while (!MainWindow->ShouldClose())
    {
        MainWindow->ProcessMessages();
        
        // 这里可以添加引擎的更新逻辑
        // 例如：渲染、物理更新、输入处理等
        
        // 简单的帧率控制（这里只是示例）
        Sleep(16); // 约60FPS
    }
#endif
    
    LOG_INFO("BoxEngine main loop ended");
}

void FLauncher::OnWindowResize(FInt32 NewWidth, FInt32 NewHeight)
{
    LOG_INFO("Window resized to " + std::to_string(NewWidth) + "x" + std::to_string(NewHeight));
    
    // 这里可以添加窗口大小改变时的处理逻辑
    // 例如：重新创建渲染目标、更新视口等
}

void FLauncher::OnWindowClose()
{
    LOG_INFO("Window close requested");
    
    // 这里可以添加窗口关闭时的处理逻辑
    // 例如：保存设置、清理资源等
} 