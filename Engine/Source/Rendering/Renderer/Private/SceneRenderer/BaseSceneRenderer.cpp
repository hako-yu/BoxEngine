#include "SceneRenderer/BaseSceneRenderer.h"

FBaseSceneRenderer::FBaseSceneRenderer(FRenderingScene* InScene, FViewport* InViewport)
	: Scene(InScene)
	, Viewport(InViewport)
{

}

FBaseSceneRenderer::~FBaseSceneRenderer()
{

}
