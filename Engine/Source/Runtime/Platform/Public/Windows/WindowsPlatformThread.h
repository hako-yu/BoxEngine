
#pragma once

#include "PlatformTypes.h"

#include <windows.h>

class FWindowsPlatformThread
{
public:
	FWindowsPlatformThread(const WCHAR* ThreadName);
	~FWindowsPlatformThread();

public:
	virtual void ThreadEntry() = 0;

private:
	uint32 ThreadId;

	HANDLE ThreadHandle;
};

typedef FWindowsPlatformThread FPlatformThread;
