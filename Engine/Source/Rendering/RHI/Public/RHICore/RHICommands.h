#pragma once

#include "RHICore/RHI.h"

#define EXECUTE_RHI_COMMAND(CommandName) FRHI::GetRHICommands()->CommandName

class FRHICommands
{
public:
	virtual void InitRHIEnvironment() = 0;
	virtual void ResetOutputWindow(void* WindowHandle, int Width, int Height) = 0;
};
