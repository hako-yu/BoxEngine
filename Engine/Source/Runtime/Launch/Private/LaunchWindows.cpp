
#include "CoreMinimal.h"

#include "Application/WindowsApp.h"
#include "Engine.h"
#include "EditorMain.h"

#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    UEngine* Engine = UEngine::CreateEngine();

    Engine->Init();
    Engine->Start();
    Engine->Exit();

    delete GEngine;
    return 0;
}
