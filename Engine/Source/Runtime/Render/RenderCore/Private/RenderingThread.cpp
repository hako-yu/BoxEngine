
#include "RenderingThread.h"

#include "RenderingRunnable.h"
#include "Thread/Runnable.h"
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

void FRenderingThread::Draw()
{
	if (GRenderThread)
	{
		GRenderThread->EnqueueEvent([](FRunnable* Runnable)
			{
				FRenderingRunnable* RenderingRunnable = static_cast<FRenderingRunnable*>(Runnable);
				RenderingRunnable->Draw();
			});
	}
}
