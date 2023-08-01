
#pragma once

#include "Thread/RunnableThread.h"

class FRHIThread
{
public:
	static void StartRHIThread();
	static void StopRHIThread();
};

extern FRunnableThread* GRHIThread;
