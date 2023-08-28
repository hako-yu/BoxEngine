
#include "CoreMinimal.h"

#include <windows.h>

#include "Engine.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GAppInstance = hInstance;

    UEngine* Engine = UEngine::CreateEngine();

    Engine->Init();
    Engine->Start();
    Engine->Exit();

    delete GEngine;
    return 0;
}
