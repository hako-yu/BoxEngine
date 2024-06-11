#pragma once

class FRenderSwapChain;
class FRenderCommandList;

class FGameViewport
{
public:
	FGameViewport();
	~FGameViewport();

	bool CreateViewport(void* AppInstance, int Width, int Height);

public:
	void ApplyViewport(FRenderCommandList* CommandList);

private:
	int Width;
	int Height;

	void* Wnd;

	FRenderSwapChain* RenderSwapChain;
};
