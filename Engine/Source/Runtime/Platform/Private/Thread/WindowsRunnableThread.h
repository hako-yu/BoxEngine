
#include "Thread/RunnableThread.h"

#include <windows.h>

class FWindowsRunnableThread : public FRunnableThread
{
private:
	HANDLE hThread;

private:
	static DWORD WINAPI _ThreadProc(LPVOID InRunnable);

	virtual void CreateInternal() override;
	virtual void Kill() override;
};
