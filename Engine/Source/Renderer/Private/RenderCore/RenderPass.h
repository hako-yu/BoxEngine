#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <vector>
#include <map>
#include <string>

using namespace Microsoft::WRL;

class FRenderDevice;
class FRenderCommandList;
class FRenderRootSignature;

class FRenderPass
{
public:
	FRenderPass(FRenderDevice* Device);
	~FRenderPass();

public:
	void ApplyRenderPass(FRenderCommandList* CommandList);

protected:
	void BuildInputLayout();
	void BuildRootSignature();
	ComPtr<ID3DBlob> BuildShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target);
	void BuildPSO();

protected:
	std::vector<D3D12_INPUT_ELEMENT_DESC> InputLayout;
	FRenderRootSignature* RootSignature;
	ComPtr<ID3D12PipelineState> PSO;

	FRenderDevice* RenderDevice;
};

class FRenderPassMap
{
public:
	enum class ERenderPassType
	{
		BlingPhone,
		Max
	};

public:
	static void Init();
	static FRenderPass* GetRenderPass(ERenderPassType Type);

private:
	static std::map<ERenderPassType, FRenderPass> RenderPassMap;
};
