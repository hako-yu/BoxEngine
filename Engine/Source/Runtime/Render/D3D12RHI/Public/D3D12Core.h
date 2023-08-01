
#pragma once

#include "RHICore.h"

#include "CoreTypes/CoreTypes.h"
#include "D3D12Minimal.h"

class FD3D12Adapter;
class FD3D12Device;
class FD3D12CommandList;
class FD3D12Viewport;

class FD3D12Core : public FRHICore
{
public:
	static FD3D12Core* Create();

protected:
	Microsoft::WRL::ComPtr<IDXGIFactory4> DxgiFactory;

	TArray<FD3D12Adapter*> AdapterList;
	FD3D12Device* Device;
	FD3D12CommandList* CommandList;
	FD3D12Viewport* MainViewport;

protected:
	void InitAdapters();
	void InitDevice();
	void CheckSupports();
	void InitCommandList();
	void InitViewport();

protected:
	virtual void Init() override;
	virtual void Draw() override;
	virtual void Release() override;

};
