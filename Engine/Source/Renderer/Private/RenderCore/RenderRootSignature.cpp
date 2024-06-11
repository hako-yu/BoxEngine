#include "RenderCore/RenderRootSignature.h"

#include "RenderCore/RenderDevice.h"

/* ====================================================================
 * FRenderRootParameter
 * ==================================================================== */
void FRenderRootParameter::InitAsConstants()
{

}

void FRenderRootParameter::InitAsConstantBufferView()
{

}

void FRenderRootParameter::InitAsShaderResourceView()
{

}

void FRenderRootParameter::InitAsUnorderedAccessView()
{

}

void FRenderRootParameter::InitAsDescriptorTable()
{

}

/* ====================================================================
 * FRenderRootSignature
 * ==================================================================== */
FRenderRootSignature::FRenderRootSignature(FRenderDevice* Device)
    : RenderDevice(Device)
{ }

FRenderRootSignature::~FRenderRootSignature()
{

}

void FRenderRootSignature::AddRootParameter(FRenderRootParameter& RootParameter)
{
    RootParameterList.push_back(RootParameter);
}

void FRenderRootSignature::Build()
{
    D3D12_ROOT_SIGNATURE_DESC RootSigDesc;
    RootSigDesc.NumParameters = RootParameterList.size();
    RootSigDesc.pParameters = RootParameterList.data();
    RootSigDesc.NumStaticSamplers = 0;
    RootSigDesc.pStaticSamplers = nullptr;
    RootSigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ComPtr<ID3DBlob> serializedRootSig = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
    HRESULT hr = D3D12SerializeRootSignature(
        &RootSigDesc,
        D3D_ROOT_SIGNATURE_VERSION_1,
        serializedRootSig.GetAddressOf(),
        errorBlob.GetAddressOf());

    /*
    if (errorBlob != nullptr)
    {
        ::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
    }
    */

    RenderDevice->GetDxDevice()->CreateRootSignature(
        0,
        serializedRootSig->GetBufferPointer(),
        serializedRootSig->GetBufferSize(),
        IID_PPV_ARGS(&DxRootSignature));
}
