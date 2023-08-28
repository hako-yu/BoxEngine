
#include "RHIThread.h"

// QueueWork is temporary plan, should be replaced by TaskGraph.
#include "QueueWork/QueueWork.h"

#include "RHIRunnable.h"
#include "Runnable/RunnableThread.h"

// QueueWork is temporary plan, should be replaced by TaskGraph.
FQueueWork<FRHICommandFunc>* GRHICommandQueueWork = nullptr;

FRHIRunnable* GRHIRunnable = nullptr;
FRunnableThread* GRHIThread = nullptr;

void FRHIThread::StartRHIThread()
{
	// QueueWork is temporary plan, should be replaced by TaskGraph.
	GRHICommandQueueWork = new FQueueWork<FRHICommandFunc>();

	GRHIRunnable = new FRHIRunnable();
	GRHIThread = FRunnableThread::Create(GRHIRunnable, L"RHI Thread");
}

void FRHIThread::StopRHIThread()
{
	if (GRHIRunnable != nullptr && GRHIThread != nullptr)
	{
		GRHIRunnable->Stop();

		// delete GRHIRunnable;
		// delete GRHIThread;
	}
}

void FRHIThread::EnqueueRHICommand(FRHICommandFunc Lambda)
{
	// QueueWork is temporary plan, should be replaced by TaskGraph.
	GRHICommandQueueWork->EnqueueEvent(Lambda);
}

void FRHIThread::FlushRHICommands()
{
	while (!GRHICommandQueueWork->IsEmpty())
	{
		FPlatformProcess::SleepForSeconds(0.01);
	}
}
