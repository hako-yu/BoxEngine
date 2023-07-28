
#pragma once

#include "CoreTypes/CoreTypes.h"
#include "Thread/Runnable.h"

class FRunnableThread
{
public:
	static FRunnableThread* Create(FRunnable* InRunnable);

	void EnqueueEvent(FRunnableEvent Lambda);

	virtual void Kill() = 0;

	void Run();
	bool IsRunning();

protected:
	// Thread Id
	uint32 ThreadID;

	// Thread Task
	FRunnable* Runnable;

protected:
	virtual void CreateInternal() = 0;
};
