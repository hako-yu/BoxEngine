#include "Renderer/SceneRenderer.h"

#include "RenderCore/RenderCore.h"
#include "RenderCore/RenderCommandList.h"
#include "RenderCore/RenderPass.h"
#include "Viewport/GameViewport.h"

FSceneRenderer::FSceneRenderer(FScene* Scene, FGameViewport* Viewport)
	: Scene(Scene)
	, Viewport(Viewport)
{ }

FSceneRenderer::~FSceneRenderer()
{ }

void FSceneRenderer::Draw()
{
	FRenderCommandList* CommandList = FRenderCore::Get()->GetRenderCommandList();
	CommandList->Reset();
	
	FRenderPassMap::GetRenderPass(FRenderPassMap::ERenderPassType::BlingPhone)->ApplyRenderPass(CommandList);
	
	Viewport->ApplyViewport(CommandList);
}
