#pragma once

class FRenderingScene;
class FViewport;
class FBaseRenderer;

enum ESceneRendererType
{
	DeferredShadingRenderer
};

class FSceneRenderer
{
public:
	FSceneRenderer();
	~FSceneRenderer();

public:
	void InitRenderer();
	void Render(FRenderingScene* InScene, FViewport* InViewport);

protected:
	ESceneRendererType SceneRendererType;
	FBaseRenderer* Renderer;
};
