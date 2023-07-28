
#include "WindowsRunnableThread.h"

#include "Thread/Runnable.h"

DWORD WINAPI FWindowsRunnableThread::_ThreadProc(LPVOID InThread)
{
	OutputDebugString("start thread\n");

	FRunnableThread* pThread = (FRunnableThread*)InThread;

	pThread->Run();

	return 0;
}

void FWindowsRunnableThread::CreateInternal()
{
	constexpr uint64 DefaultStackSize = 1024 * 1024;
	// hThread = CreateThread(NULL, DefaultStackSize, _ThreadProc, Runnable, STACK_SIZE_PARAM_IS_A_RESERVATION | CREATE_SUSPENDED, (DWORD*)&ThreadID);
	hThread = CreateThread(NULL, DefaultStackSize, _ThreadProc, this, 0, (DWORD*)&ThreadID);

	if (hThread)
	{
		SetThreadDescription(hThread, ThreadName.c_str());
	}
}

void FWindowsRunnableThread::Kill()
{
	if (Runnable)
	{
		Runnable->Kill();

		// When Thread is Exitted, CloseHandle(hThread);
	}
}
