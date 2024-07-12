#include "SceneRenderer/DeferredShadingRenderer.h"

#include "RHICore/RHICommands.h"

FDeferredShadingRenderer::FDeferredShadingRenderer()
{

}

FDeferredShadingRenderer::~FDeferredShadingRenderer()
{

}

void FDeferredShadingRenderer::InitPass()
{

}

void FDeferredShadingRenderer::Render()
{
    EXECUTE_RHI_COMMAND(BeginFrame)();

    EXECUTE_RHI_COMMAND(EndFrame)();
}
