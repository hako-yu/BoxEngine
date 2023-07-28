
#include "RHIRunnable.h"

#include "D3D12Core.h"

bool FRHIRunnable::NativeInit()
{
#ifdef D3D12_SUPPORTS
	RHICore = new FD3D12Core();
#endif // D3D12_SUPPORTS

	if (RHICore == nullptr)
	{
		return false;
	}
	
	RHICore->Init();

	RHICore->Draw();

	return true;
}

void FRHIRunnable::NativeExit()
{

}
