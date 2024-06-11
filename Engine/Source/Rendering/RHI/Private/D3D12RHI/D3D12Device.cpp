#include "D3D12RHI/D3D12Device.h"

FD3D12Device::FD3D12Device()
{
	HRESULT HRes;
	HRes = CreateDXGIFactory(IID_PPV_ARGS(&DxFactory));
	ThrowIfFailed(HRes);

	HRes = D3D12CreateDevice(
		nullptr, // default adapter
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&DxDevice)
	);
	ThrowIfFailed(HRes);
}

FD3D12Device::~FD3D12Device()
{

}
