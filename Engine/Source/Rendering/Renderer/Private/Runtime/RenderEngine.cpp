#include "Runtime/RenderEngine.h"

#include "Viewport/Viewport.h"
#include "Scene/RenderingScene.h"
#include "RHICore/RHI.h"

extern void* GInstance;

FRenderEngine::FRenderEngine()
{

}

FRenderEngine::~FRenderEngine()
{

}

bool FRenderEngine::Init()
{
	// Init RHI
	FRHI::Init();

	// Init Viewport
	MainViewport = new FViewport();
	MainViewport->AddToWindow(GInstance);

	// Init Rendering Scene
	Scene = new FRenderingScene();

	return true;
}

void FRenderEngine::Tick()
{
	MainViewport->Update();
}

void FRenderEngine::Exit()
{
	delete MainViewport;
	delete Scene;

	FRHI::Exit();
}
