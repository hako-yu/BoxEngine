
#include "SceneRenderer.h"

#include "Scene.h"

FSceneRenderer::FSceneRenderer(FScene* InScene, FCanvas* InCanvas)
	: Scene(InScene)
	, Canvas(InCanvas)
{

}

void FSceneRenderer::Render()
{
	/*
	FRHIThread::EnqueueRHICommand([](FRHI* RHICmdList)
		{

		});
	*/
}
