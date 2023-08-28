
#pragma once

#include "CoreMinimal.h"
#include "D3D12Utils.h"

class FD3D12Resource
{
public:
	FD3D12Resource();
	~FD3D12Resource();

public:
	ID3D12Resource* GetDxResource() { return DxResource.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> DxResource;
};
