#include "RHICore/RHI.h"

#include "RHICore/DynamicRHI.h"

// D3D12
#include "D3D12RHI/D3D12RHI.h"

void FRHI::Init()
{
	// D3D12
	FD3D12RHI::Create();

	FDynamicRHI::Get()->EnableDebug();
	FDynamicRHI::Get()->Init();
}

void FRHI::Exit()
{
	FDynamicRHI::Get()->Exit();
}
