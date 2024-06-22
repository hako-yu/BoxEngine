#pragma once

#define EXECUTE_RHI_COMMAND(CommandName) FRHICommands::Get()->CommandName

class FRHICommands
{
public:
	static FRHICommands* Get();

public:
	virtual void InitRHIEnvironment() = 0;
	virtual void ResetOutputWindow(void* WindowHandle, int Width, int Height) = 0;

	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
};
