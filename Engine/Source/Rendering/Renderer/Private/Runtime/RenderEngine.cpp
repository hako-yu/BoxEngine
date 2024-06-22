#include "Runtime/RenderEngine.h"

#include "RHICore/RHI.h"
#include "RHICore/RHICommands.h"
#include "Viewport/Viewport.h"
#include "Scene/RenderingScene.h"
#include "SceneRenderer/DeferredShadingRenderer.h"

// Test
#include "TestScene/TestScene.h"

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
	EXECUTE_RHI_COMMAND(InitRHIEnvironment)();

	// Init Viewport
	MainViewport = new FViewport();
	MainViewport->AddToWindow(GInstance);

	// Init Rendering Scene
	Scene = new FRenderingScene();

	// Build Test Scene
	FTestSceneBuildingFunction::BuildTestScene(Scene);

	return true;
}

void FRenderEngine::Tick()
{
	// Scene Renderer
	FDeferredShadingRenderer Renderer(Scene, MainViewport);
	Renderer.Render();

	MainViewport->Update();
}

void FRenderEngine::Exit()
{
	delete MainViewport;
	delete Scene;

	FRHI::Exit();
}
