
#include "Thread/RunnableThread.h"

#ifdef PLATFORM_WINDOWS
#include "WindowsRunnableThread.h"
#endif // PLATFORM_WINDOWS

FRunnableThread* FRunnableThread::Create(FRunnable* InRunnable)
{
    FRunnableThread* NewThread = nullptr;

#ifdef PLATFORM_WINDOWS
	NewThread = new FWindowsRunnableThread();
#endif // PLATFORM_WINDOWS

    if (NewThread)
    {
	    NewThread->Runnable = InRunnable;
	    NewThread->CreateInternal();
    }

	return NewThread;
}

void FRunnableThread::EnqueueEvent(FRunnableEvent Lambda)
{
    if (Runnable)
    {
        Runnable->EventQueue.Push(Lambda);
    }
}

void FRunnableThread::Run()
{
    if (Runnable)
    {
        // Run
        Runnable->Init();

        // Exit
        delete Runnable;
    }
}

bool FRunnableThread::IsRunning()
{
    if (Runnable)
    {
        return Runnable->Status.Get() == ERunnableStatus::Running;
    }

    return false;
}
