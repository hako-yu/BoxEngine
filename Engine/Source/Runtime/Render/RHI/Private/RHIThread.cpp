
#include "RHIThread.h"

#include "RHIRunnable.h"
#include "Thread/RunnableThread.h"

FRunnableThread* GRHIThread = nullptr;

void FRHIThread::StartRHIThread()
{
	FRHIRunnable* RHIRunnable = new FRHIRunnable();
	GRHIThread = FRunnableThread::Create(RHIRunnable);
}

void FRHIThread::StopRHIThread()
{
	if (GRHIThread)
	{
		GRHIThread->Kill();
		delete GRHIThread;
	}
}
