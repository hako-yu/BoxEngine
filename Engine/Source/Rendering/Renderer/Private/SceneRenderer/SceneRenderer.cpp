#include "SceneRenderer/SceneRenderer.h"

#include "SceneRenderer/DeferredShadingRenderer.h"

FSceneRenderer::FSceneRenderer()
	: SceneRendererType(ESceneRendererType::DeferredShadingRenderer)
{
	InitRenderer();
}

FSceneRenderer::~FSceneRenderer()
{

}

void FSceneRenderer::InitRenderer()
{
	if (SceneRendererType == ESceneRendererType::DeferredShadingRenderer)
	{
		Renderer = new FDeferredShadingRenderer();
		Renderer->InitPass();
	}
}

void FSceneRenderer::Render(FRenderingScene* InScene, FViewport* InViewport)
{
	Renderer->SetRenderEnvironment(InScene, InViewport);
	Renderer->Render();
}
