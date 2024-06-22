#include "RHICore/RHICommands.h"

#include "RHICore/DynamicRHI.h"

FRHICommands* FRHICommands::Get()
{
	return FDynamicRHI::GetRHICommands();
}
