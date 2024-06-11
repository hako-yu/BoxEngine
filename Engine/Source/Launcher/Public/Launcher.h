#pragma once

class FLauncher
{
public:
    FLauncher();
    ~FLauncher();

public:
    bool Init();
    void Run();
    void Exit();

private:
    class FRenderEngine* RenderEngine;
};
