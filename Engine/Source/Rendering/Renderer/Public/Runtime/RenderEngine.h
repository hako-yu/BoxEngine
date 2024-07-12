#pragma once

class FViewport;
class FRenderingScene;
class FMeshProcessor;
class FSceneRenderer;

class FRenderEngine
{
public:
	FRenderEngine();
	~FRenderEngine();

public:
	bool Init();
	void Tick();
	void Exit();

private:
	FViewport* MainViewport = nullptr;
	FRenderingScene* Scene = nullptr;
	FMeshProcessor* MeshProcessor = nullptr;
	FSceneRenderer* SceneRenderer = nullptr;
};
