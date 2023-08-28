
#include "RenderingThread.h"

// QueueWork is temporary plan, should be replaced by TaskGraph.
#include "QueueWork/QueueWork.h"

#include "RenderingRunnable.h"
#include "Runnable/RunnableThread.h"

// QueueWork is temporary plan, should be replaced by TaskGraph.
FQueueWork<FRenderingCommandFunc>* GRenderingCommandQueueWork = nullptr;

FRenderingRunnable* GRenderingRunnable = nullptr;
FRunnableThread* GRenderingThread = nullptr;

void FRenderingThread::StartRenderingThread()
{
	// QueueWork is temporary plan, should be replaced by TaskGraph.
	GRenderingCommandQueueWork = new FQueueWork<FRenderingCommandFunc>();

	GRenderingRunnable = new FRenderingRunnable();
	GRenderingThread = FRunnableThread::Create(GRenderingRunnable, L"Render Thread");
}

void FRenderingThread::StopRenderingThread()
{
	if (GRenderingRunnable != nullptr && GRenderingThread != nullptr)
	{
		GRenderingRunnable->Stop();

		// delete GRenderingRunnable;
		// delete GRenderingThread;
	}
}

void FRenderingThread::EnqueueRenderingCommand(FRenderingCommandFunc Lambda)
{
	// QueueWork is temporary plan, should be replaced by TaskGraph.
	GRenderingCommandQueueWork->EnqueueEvent(Lambda);
}

void FRenderingThread::FlushRenderingCommands()
{
	while (!GRenderingCommandQueueWork->IsEmpty())
	{
		FPlatformProcess::SleepForSeconds(0.01);
	}
}
