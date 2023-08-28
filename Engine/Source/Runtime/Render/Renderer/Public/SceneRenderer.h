
#pragma once

class FScene;
class FCanvas;

class FSceneRenderer
{
public:
	FSceneRenderer(FScene* InScene, FCanvas* InCanvas);

	void Render();

private:
	FScene* Scene;
	FCanvas* Canvas;
};
