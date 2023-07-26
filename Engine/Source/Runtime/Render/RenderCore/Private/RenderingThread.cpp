
#include "RenderingThread.h"

#include "RenderingRunnable.h"
#include "Thread/RunnableThread.h"

FRunnableThread* GRenderThread = nullptr;

void FRenderingThread::StartRenderingThread()
{
	FRenderingRunnable* RenderingRunnable = new FRenderingRunnable();
	GRenderThread = FRunnableThread::Create(RenderingRunnable);
}

void FRenderingThread::StopRenderingThread()
{
	if (GRenderThread)
	{
		GRenderThread->Kill();
		delete GRenderThread;
	}
}
