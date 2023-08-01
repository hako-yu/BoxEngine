
#include "RenderingRunnable.h"

#include "RHIThread.h"
#include "RHICore.h"

void FRenderingRunnable::Draw()
{
	if (GRHIThread && GRHIThread->IsRunning())
	{
		GRHIThread->EnqueueEvent([](FRunnable* Runnable)
			{
				GRHICore->Draw();
			});
	}
}

bool FRenderingRunnable::NativeInit()
{
	return true;
}

void FRenderingRunnable::NativeExit()
{

}
