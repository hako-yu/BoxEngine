
#pragma once

#include "CoreMinimal.h"
#include "RHI.h"
#include "D3D12ThirdParty.h"

class FRHICommandList;
class FD3D12Adapter;

class FD3D12RHI : public FRHI
{
public:
	FD3D12RHI();
	~FD3D12RHI();

protected:
	virtual void Init() override;
	virtual FRHIViewport* CreateViewport(void* WindowHandle, uint32 SizeX, uint32 SizeY) override;

private:
	Microsoft::WRL::ComPtr<IDXGIFactory2> DxgiFactory2;

	TArray<FD3D12Adapter*> AdapterList;
	FD3D12Adapter* CurrentAdapter = nullptr;
};
