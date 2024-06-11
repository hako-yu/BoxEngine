#include "RenderCore/RenderPass.h"

#include "Logging.h"
#include "RenderCore/RenderCore.h"
#include "RenderCore/RenderDevice.h"
#include "RenderCore/RenderCommandList.h"
#include "RenderCore/RenderRootSignature.h"

FRenderPass::FRenderPass(FRenderDevice* Device)
    : RenderDevice(Device)
{
    BuildInputLayout();
    BuildRootSignature();
    BuildPSO();
}

FRenderPass::~FRenderPass()
{

}

void FRenderPass::ApplyRenderPass(FRenderCommandList* CommandList)
{
    ID3D12CommandAllocator* DxCommandAllocator = CommandList->GetDxCommandAllocator();
    ID3D12GraphicsCommandList* DxCommandList = CommandList->GetDxCommandList();

    DxCommandAllocator->Reset();
    DxCommandList->Reset(DxCommandAllocator, PSO.Get());
}

void FRenderPass::BuildInputLayout()
{
    InputLayout =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
    };
}

void FRenderPass::BuildRootSignature()
{
    FRenderCore* RenderCore = FRenderCore::Get();
    RootSignature = new FRenderRootSignature(RenderCore->GetRenderDevice());

    FRenderRootParameter RootParameter;
    RootParameter.InitAsDescriptorTable();

    RootSignature->AddRootParameter(RootParameter);
    RootSignature->Build();
}

ComPtr<ID3DBlob> FRenderPass::BuildShader(
    const std::wstring& filename,
    const D3D_SHADER_MACRO* defines,
    const std::string& entrypoint,
    const std::string& target)
{
    UINT compileFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)  
    compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    HRESULT hr = S_OK;

    std::wstring ShaderPath(SHADER_ROOT_PATH);
    ShaderPath += filename;

    ComPtr<ID3DBlob> byteCode = nullptr;
    ComPtr<ID3DBlob> errors;
    hr = D3DCompileFromFile(ShaderPath.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
        entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode, &errors);

    if (errors != nullptr)
    {
        BOX_LOG((char*)errors->GetBufferPointer());
    }

    return byteCode;
}

void FRenderPass::BuildPSO()
{
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
    ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
    psoDesc.InputLayout = { InputLayout.data(), (UINT)InputLayout.size() };
    psoDesc.pRootSignature = RootSignature->GetDxRootSignature();
    ComPtr<ID3DBlob> VsShader = BuildShader(L"BlingPhone.hlsl", nullptr, "VS", "vs_5_0");
    psoDesc.VS =
    {
        reinterpret_cast<BYTE*>(VsShader->GetBufferPointer()),
        VsShader->GetBufferSize()
    };
    ComPtr<ID3DBlob> PsShader = BuildShader(L"BlingPhone.hlsl", nullptr, "PS", "ps_5_0");
    psoDesc.PS =
    {
        reinterpret_cast<BYTE*>(PsShader->GetBufferPointer()),
        PsShader->GetBufferSize()
    };

    D3D12_RASTERIZER_DESC RasterizerDesc;
    RasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
    RasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
    RasterizerDesc.FrontCounterClockwise = FALSE;
    RasterizerDesc.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
    RasterizerDesc.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
    RasterizerDesc.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
    RasterizerDesc.DepthClipEnable = TRUE;
    RasterizerDesc.MultisampleEnable = FALSE;
    RasterizerDesc.AntialiasedLineEnable = FALSE;
    RasterizerDesc.ForcedSampleCount = 0;
    RasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
    psoDesc.RasterizerState = RasterizerDesc;

    D3D12_BLEND_DESC BlendDesc;
    BlendDesc.AlphaToCoverageEnable = FALSE;
    BlendDesc.IndependentBlendEnable = FALSE;
    const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
    {
        FALSE,FALSE,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_LOGIC_OP_NOOP,
        D3D12_COLOR_WRITE_ENABLE_ALL,
    };
    for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        BlendDesc.RenderTarget[i] = defaultRenderTargetBlendDesc;
    }
    psoDesc.BlendState = BlendDesc;

    D3D12_DEPTH_STENCIL_DESC DepthStencilDesc;
    DepthStencilDesc.DepthEnable = TRUE;
    DepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    DepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
    DepthStencilDesc.StencilEnable = FALSE;
    DepthStencilDesc.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
    DepthStencilDesc.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
    const D3D12_DEPTH_STENCILOP_DESC defaultStencilOp =
    { D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_STENCIL_OP_KEEP, D3D12_COMPARISON_FUNC_ALWAYS };
    DepthStencilDesc.FrontFace = defaultStencilOp;
    DepthStencilDesc.BackFace = defaultStencilOp;
    psoDesc.DepthStencilState = DepthStencilDesc;

    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.SampleDesc.Count = 1;
    psoDesc.SampleDesc.Quality = 0;
    psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
    RenderDevice->GetDxDevice()->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&PSO));
}

void FRenderPassMap::Init()
{
    RenderPassMap = std::map<ERenderPassType, FRenderPass>();

    FRenderPass BlingPhonePass(FRenderCore::Get()->GetRenderDevice());
    RenderPassMap.insert(std::pair<ERenderPassType, FRenderPass>(ERenderPassType::BlingPhone, BlingPhonePass));
}

FRenderPass* FRenderPassMap::GetRenderPass(ERenderPassType Type)
{
    return &RenderPassMap[Type];
}
