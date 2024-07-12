#pragma once

#include "RHICore/RHICommands.h"

class FD3D12RHI;

class FD3D12Commands : public FRHICommands
{
public:
	virtual void InitRHIEnvironment() override;
	virtual void ResetOutputWindow(void* WindowHandle, int Width, int Height) override;

	virtual FRHIGeometry* CreateRHIGeometry() override;
	virtual void DestroyRHIGeometry(FRHIGeometry* Geometry) override;

	virtual void ResetVertexLayout() override;
	virtual void AddVertexLayoutItem(const FString& Name, ERHIVertexLayoutItemFormat Format) override;

	virtual FRHIPass* NewPass(ERHIPassType PassType) override;

	virtual void BeginFrame() override;
	virtual void EndFrame() override;
};
