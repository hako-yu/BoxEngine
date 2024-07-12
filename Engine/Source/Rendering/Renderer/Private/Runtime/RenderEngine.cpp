#include "Runtime/RenderEngine.h"

#include "RHICore/RHI.h"
#include "RHICore/RHICommands.h"
#include "Viewport/Viewport.h"
#include "Scene/RenderingScene.h"
#include "MeshProcessor/MeshProcessor.h"
#include "SceneRenderer/SceneRenderer.h"

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

	// Init Scene Renderer
	SceneRenderer = new FSceneRenderer();

	// Init Mesh Processor
	MeshProcessor = new FMeshProcessor();

	// Init Rendering Scene
	Scene = new FRenderingScene();

	// Build Test Scene
	FTestSceneBuildingFunction::BuildTestScene(Scene);

	return true;
}

void FRenderEngine::Tick()
{
	// Scene Renderer
	SceneRenderer->Render(Scene, MainViewport);

	MainViewport->Update();
}

void FRenderEngine::Exit()
{
	delete MainViewport;
	delete Scene;

	FRHI::Exit();
}
