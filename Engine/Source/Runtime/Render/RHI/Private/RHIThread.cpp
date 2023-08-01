
#include "RHIThread.h"

#include "RHIRunnable.h"
#include "RHICore.h"

FRunnableThread* GRHIThread = nullptr;

void FRHIThread::StartRHIThread()
{
	FRHIRunnable* RHIRunnable = new FRHIRunnable();
	GRHIThread = FRunnableThread::Create(RHIRunnable, L"RHI Thread");
}

void FRHIThread::StopRHIThread()
{
	if (GRHIThread)
	{
		GRHIThread->Kill();
		delete GRHIThread;
	}
}
