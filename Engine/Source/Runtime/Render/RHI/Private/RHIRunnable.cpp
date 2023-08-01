
#include "RHIRunnable.h"

#include "D3D12Core.h"

FRHICore* GRHICore = nullptr;

bool FRHIRunnable::NativeInit()
{
#ifdef D3D12_SUPPORTS
	GRHICore = FD3D12Core::Create();
#endif // D3D12_SUPPORTS

	if (GRHICore == nullptr)
	{
		return false;
	}
	
	GRHICore->Init();

	return true;
}

void FRHIRunnable::NativeExit()
{
	if (GRHICore)
	{
		GRHICore->Release();
		delete GRHICore;
	}
}
