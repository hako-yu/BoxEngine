
#include "RHICore.h"

#include "D3D12RHI.h"

FRHICore* GRHICore = nullptr;

void FRHICore::InitRHICore()
{
	if (GRHICore != nullptr)
	{
		return;
	}

	GRHICore = new FRHICore();

	FRHI* D3D12RHI = new FD3D12RHI();
	D3D12RHI->Init();
	GRHICore->RHIList.Add(D3D12RHI);
	GRHICore->CurrentRHI = D3D12RHI;
}

FRHI* FRHICore::GetCurrentRHI()
{
	return GRHICore->CurrentRHI;
}

void FRHICore::SwitchRHI()
{

}
