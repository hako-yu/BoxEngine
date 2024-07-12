#pragma once

class FRenderingScene;
class FViewport;

class FBaseRenderer
{
public:
	FBaseRenderer();
	~FBaseRenderer();

public:
	virtual void InitPass() = 0;
	virtual void Render() = 0;

public:
	void SetRenderEnvironment(FRenderingScene* InScene, FViewport* InViewport);
protected:
	FRenderingScene* Scene = nullptr;
	FViewport* Viewport = nullptr;
};
