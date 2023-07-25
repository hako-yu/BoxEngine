
#pragma once

class IPlatformAppCallbackInterface
{
public:
    virtual void OnActivate() = 0;
    virtual void OnDestory() = 0;

    virtual void OnResize() = 0;

    virtual void OnMouseDown() = 0;
    virtual void OnMouseUp() = 0;
    virtual void OnMouseMove() = 0;
};
extern IPlatformAppCallbackInterface* PlatformAppProc;

struct FPlatformAppConfig
{
    int Width = 1024;
    int Height = 768;
};
extern FPlatformAppConfig PlatformAppConfig;

class FPlatformApplication
{
public:
    static void CreateMainWindow();
    static void ShowMainWindow();
    static void PumpMessages();
};
