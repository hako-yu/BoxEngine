#pragma once

class FScene;
class FGameViewport;

class FSceneRenderer
{
public:
	FSceneRenderer(FScene* Scene, FGameViewport* Viewport);
	~FSceneRenderer();

public:
	void Draw();

private:
	FScene* Scene;
	FGameViewport* Viewport;
};
