
#include "Windows/WindowsPlatformThread.h"

DWORD WINAPI _ThreadProc(LPVOID InThread)
{
	OutputDebugString("start thread\n");

	FWindowsPlatformThread* pThread = (FWindowsPlatformThread*)InThread;

	pThread->ThreadEntry();

	return 0;
}

FWindowsPlatformThread::FWindowsPlatformThread(const WCHAR* ThreadName)
{
	ThreadHandle = CreateThread(NULL, 0, _ThreadProc, this, 0, (DWORD*)&ThreadId);

	if (ThreadHandle)
	{
		SetThreadDescription(ThreadHandle, ThreadName);
	}
}

FWindowsPlatformThread::~FWindowsPlatformThread()
{

}
