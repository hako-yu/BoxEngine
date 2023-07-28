
#include "WindowsD3D12Adapter.h"

FWindowsD3D12Adapter::FWindowsD3D12Adapter()
{
	ReturnIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory)));
}

FWindowsD3D12Adapter::~FWindowsD3D12Adapter()
{
	mdxgiFactory->Release();
}
