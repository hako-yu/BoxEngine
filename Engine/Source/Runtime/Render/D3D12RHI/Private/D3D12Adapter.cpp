
#include "D3D12Adapter.h"

FD3D12Adapter* FD3D12Adapter::Create(IDXGIAdapter* InAdapter)
{
	FD3D12Adapter* DxAdapter = new FD3D12Adapter();

	if (DxAdapter)
	{
		DxAdapter->DxgiAdapter = InAdapter;
	}
	return DxAdapter;
}
