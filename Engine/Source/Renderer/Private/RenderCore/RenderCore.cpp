#include "RenderCore/RenderCore.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

#include "RenderCore/RenderDevice.h"
#include "RenderCore/RenderCommandList.h"
#include "RenderCore/RenderSwapChain.h"

void FRenderCore::Create()
{
	if (GRenderCore)
	{
		return;
	}

	GRenderCore = new FRenderCore();
	GRenderCore->Init();
}

FRenderSwapChain* FRenderCore::CreateSwapChain()
{
	FRenderSwapChain* RenderSwapChain = new FRenderSwapChain();
	RenderSwapChain->Init(RenderDevice, RenderCommandList);

	return RenderSwapChain;
}

void FRenderCore::Init()
{
	RenderDevice = new FRenderDevice();
	RenderDevice->Init();

	RenderCommandList = new FRenderCommandList();
	RenderCommandList->Init(RenderDevice);
}
