#include "RenderCore/RenderDevice.h"

void FRenderDevice::Init()
{
	// Init Factory
	CreateDXGIFactory(IID_PPV_ARGS(&DxFactory));

	// Init Adapter
	DxFactory->EnumAdapters(0, DxAdapter.GetAddressOf());

	// Init Device
	D3D12CreateDevice(DxAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&DxDevice));
}

