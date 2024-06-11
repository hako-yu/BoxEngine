#pragma once

class FViewport;
class FRenderingScene;
class FRHI;

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
};
