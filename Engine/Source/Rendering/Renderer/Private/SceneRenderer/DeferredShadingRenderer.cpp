#include "SceneRenderer/DeferredShadingRenderer.h"

#include "RHICore/RHICommands.h"

FDeferredShadingRenderer::FDeferredShadingRenderer(FRenderingScene* InScene, FViewport* InViewport)
    : FBaseSceneRenderer(InScene, InViewport)
{

}

FDeferredShadingRenderer::~FDeferredShadingRenderer()
{

}

void FDeferredShadingRenderer::Render()
{
    EXECUTE_RHI_COMMAND(BeginFrame)();

    EXECUTE_RHI_COMMAND(EndFrame)();
}
