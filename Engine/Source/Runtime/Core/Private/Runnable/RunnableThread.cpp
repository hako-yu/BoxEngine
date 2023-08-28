
#include "Runnable/RunnableThread.h"

#include "Runnable/Runnable.h"

FRunnableThread* FRunnableThread::Create(FRunnable* InRunnable, const WCHAR* ThreadName, uint32 InStackSize)
{
	FRunnableThread* Thread = new FRunnableThread(ThreadName);
	Thread->Runnable = InRunnable;
	return Thread;
}

void FRunnableThread::ThreadEntry()
{
	Runnable->Init();
	Runnable->Run();
	Runnable->Exit();
}
