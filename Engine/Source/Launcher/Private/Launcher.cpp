#include "Launcher.h"

#include <windows.h>

#include "Logging.h"
#include "Runtime/RenderEngine.h"

void* GInstance = nullptr;

/* ====================================================================
 * WIN API
 * ==================================================================== */
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    GInstance = hInstance;

    FLauncher* Launcher = new FLauncher();

    if (Launcher->Init())
    {
        Launcher->Run();
    }
    Launcher->Exit();

    return 0;
}


/* ====================================================================
 * FLauncher
 * ==================================================================== */
FLauncher::FLauncher()
{
    RenderEngine = new FRenderEngine();
}

FLauncher::~FLauncher()
{
    if (RenderEngine)
    {
        delete RenderEngine;
    }
}

bool FLauncher::Init()
{
    if (!RenderEngine->Init())
    {
        BOX_LOG("Render Engine Init Failed !!");
        return false;
    }

    return true;
}

void FLauncher::Run()
{
    MSG msg = { 0 };

    // Loop
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Sleep(100);
            RenderEngine->Tick();
        }
    }
}

void FLauncher::Exit()
{
    RenderEngine->Exit();
}
