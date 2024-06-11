#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <vector>

using namespace Microsoft::WRL;

struct FRenderRootParameter : public D3D12_ROOT_PARAMETER
{
public:
	// Constant
	void InitAsConstants();

	// CBV
	void InitAsConstantBufferView();

	// SRV
	void InitAsShaderResourceView();

	// UAV
	void InitAsUnorderedAccessView();

	// DescriptorTable
	void InitAsDescriptorTable();
};

class FRenderRootSignature
{
public:
	FRenderRootSignature(FRenderDevice* Device);
	~FRenderRootSignature();

public:
	void AddRootParameter(FRenderRootParameter& RootParameter);
	void Build();
	ID3D12RootSignature* GetDxRootSignature() { return DxRootSignature.Get(); }

private:
	std::vector<FRenderRootParameter> RootParameterList;
	ComPtr<ID3D12RootSignature> DxRootSignature;

	FRenderDevice* RenderDevice;
};
