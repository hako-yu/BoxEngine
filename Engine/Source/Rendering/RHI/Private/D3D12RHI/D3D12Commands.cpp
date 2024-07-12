#include "D3D12RHI/D3D12Commands.h"

#include "D3D12RHICommon.h"
#include "D3D12RHI/D3D12RHI.h"
#include "D3D12RHI/D3D12Adapter.h"
#include "D3D12RHI/D3D12Viewport.h"
#include "D3D12RHI/D3D12Geometry.h"
#include "D3D12RHI/D3D12Pass.h"

void FD3D12Commands::InitRHIEnvironment()
{
	FD3D12RHI::Get()->InitRootAdapter();
}

void FD3D12Commands::ResetOutputWindow(void* WindowHandle, int Width, int Height)
{
	FD3D12Adapter* Adapter = FD3D12RHI::Get()->GetRootAdapter();
	FD3D12Viewport* MainViewport = Adapter->GetMainViewport();
	if (MainViewport == nullptr)
	{
		MainViewport = Adapter->CreateMainViewport();
	}
	MainViewport->InitSwapChain(WindowHandle, Width, Height);
}

FRHIGeometry* FD3D12Commands::CreateRHIGeometry()
{
	FD3D12Adapter* Adapter = FD3D12RHI::Get()->GetRootAdapter();
	FD3D12Device* Device = Adapter->GetRootDevice();
	return new FD3D12Geometry(Device);
}

void FD3D12Commands::DestroyRHIGeometry(FRHIGeometry* Geometry)
{
	delete Geometry;
}

void FD3D12Commands::ResetVertexLayout()
{

}

void FD3D12Commands::AddVertexLayoutItem(const FString& Name, ERHIVertexLayoutItemFormat Format)
{

}

FRHIPass* FD3D12Commands::NewPass(ERHIPassType PassType)
{
	FD3D12Adapter* Adapter = FD3D12RHI::Get()->GetRootAdapter();
	return Adapter->FindOrAddPass(PassType);
}

void FD3D12Commands::BeginFrame()
{

}

void FD3D12Commands::EndFrame()
{
	FD3D12Adapter* Adapter = FD3D12RHI::Get()->GetRootAdapter();
	FD3D12Pass OnePass(Adapter);
	OnePass.Run();
}

