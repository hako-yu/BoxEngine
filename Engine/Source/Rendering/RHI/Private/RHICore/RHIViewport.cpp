#include "RHICore/RHIViewport.h"
#include "RHICore/DynamicRHI.h"

FRHIViewport* FRHIViewport::Create()
{
	return FDynamicRHI::Get()->CreateRHIViewport();
}
