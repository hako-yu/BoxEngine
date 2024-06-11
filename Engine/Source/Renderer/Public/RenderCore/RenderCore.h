#pragma once

class FRenderDevice;
class FRenderCommandList;

class FRenderCore
{
public:
	static FRenderCore* Get() { return GRenderCore; }
	static void Create();

private:
	static FRenderCore* GRenderCore;

public:
	FRenderDevice* GetRenderDevice() { return RenderDevice; }
	FRenderCommandList* GetRenderCommandList() { return RenderCommandList; }

	class FRenderSwapChain* CreateSwapChain();

private:
	void Init();

private:
	FRenderDevice* RenderDevice;
	FRenderCommandList* RenderCommandList;
};
