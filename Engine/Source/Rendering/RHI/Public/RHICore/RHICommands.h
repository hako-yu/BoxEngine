#pragma once

#include "CoreMinimal.h"
#include "RHICore/RHICommon.h"

class FRHIGeometry;
class FRHIPass;

class FRHICommands
{
public:
	static FRHICommands* Get();

public:
	virtual void InitRHIEnvironment() = 0;
	virtual void ResetOutputWindow(void* WindowHandle, int Width, int Height) = 0;

	virtual FRHIGeometry* CreateRHIGeometry() = 0;
	virtual void DestroyRHIGeometry(FRHIGeometry* Geometry) = 0;

	virtual void ResetVertexLayout() = 0;
	virtual void AddVertexLayoutItem(const FString& Name, ERHIVertexLayoutItemFormat Format) = 0;

	virtual FRHIPass* NewPass(ERHIPassType PassType) = 0;

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
};

#define EXECUTE_RHI_COMMAND(CommandName) FRHICommands::Get()->CommandName
