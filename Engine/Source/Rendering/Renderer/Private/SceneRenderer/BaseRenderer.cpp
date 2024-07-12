#include "SceneRenderer/BaseRenderer.h"

FBaseRenderer::FBaseRenderer()
{

}

FBaseRenderer::~FBaseRenderer()
{

}

void FBaseRenderer::SetRenderEnvironment(FRenderingScene* InScene, FViewport* InViewport)
{
	Scene = InScene;
	Viewport = InViewport;
}
