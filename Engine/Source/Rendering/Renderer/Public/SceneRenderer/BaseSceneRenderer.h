#pragma once

class FRenderingScene;
class FViewport;

class FBaseSceneRenderer
{
public:
	FBaseSceneRenderer(FRenderingScene* InScene, FViewport* InViewport);
	~FBaseSceneRenderer();

public:
	virtual void Render() = 0;

private:
	FRenderingScene* Scene;
	FViewport* Viewport;
};
