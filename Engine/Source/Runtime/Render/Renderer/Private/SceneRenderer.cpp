
#include "SceneRenderer.h"

#include "RHIThread.h"

FSceneRenderer::FSceneRenderer(FScene* InScene, FCanvas* InCanvas)
	: Scene(InScene)
	, Canvas(InCanvas)
{

}

void FSceneRenderer::Render()
{
	FRHIThread::EnqueueRHICommand([](FRHI* RHICmdList)
		{
			// RHICmdList->Draw();
		});
}
