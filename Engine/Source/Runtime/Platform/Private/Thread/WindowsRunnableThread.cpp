
#include "WindowsRunnableThread.h"

#include "Thread/Runnable.h"

FRunnableThread* FRunnableThread::Create(FRunnable* InRunnable)
{
	FRunnableThread* NewThread = new FWindowsRunnableThread();
	
	NewThread->Runnable = InRunnable;

	return NewThread;
}

DWORD WINAPI FWindowsRunnableThread::_ThreadProc(LPVOID InRunnable)
{
	FRunnable* pRunnable = (FRunnable*)InRunnable;

	pRunnable->Init();

	return 0;
}

void FWindowsRunnableThread::CreateInternal()
{
	constexpr uint64 DefaultStackSize = 1024 * 1024;
	CreateThread(NULL, DefaultStackSize, _ThreadProc, Runnable, STACK_SIZE_PARAM_IS_A_RESERVATION | CREATE_SUSPENDED, (DWORD*)&ThreadID);
}

void FWindowsRunnableThread::Kill()
{
	if (Runnable)
	{
		Runnable->Stop();
		delete Runnable;
	}

	CloseHandle(hThread);
}
