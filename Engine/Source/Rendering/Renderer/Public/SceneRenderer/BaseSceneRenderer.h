#pragma once

class FRenderingScene;
class FViewport;

class FBaseSceneRenderer
{
public:
	FBaseSceneRenderer(FRenderingScene* InScene, FViewport* InViewport);
	~FBaseSceneRenderer();

public:
	void Render();

private:
	FRenderingScene* Scene;
	FViewport* Viewport;
};
