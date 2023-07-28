
#pragma once

#include "CoreTypes/CoreTypes.h"
#include <shared_mutex>

enum ERunnableStatus
{
	None = 0,
	Created,
	Running,
	Killing,
	Exitted
};

class FRunnableStatus_ThreadSafe
{
public:
	void Set(ERunnableStatus InStatus);
	ERunnableStatus Get();

private:
	ERunnableStatus Status;
	std::shared_mutex Mutex;
};

typedef void (*FRunnableEvent)(class FRunnable* Runnable);

class FRunnableEventQueue
{
public:
	void Push(FRunnableEvent Lambda);
	FRunnableEvent* Pop();

private:
	TQueue<FRunnableEvent> Queue;
	std::shared_mutex Mutex;
};

class FRunnable
{
	friend class FRunnableThread;

public:
    void Init();
    void Run();
	void Exit();

	void Kill();

protected:
	FRunnableStatus_ThreadSafe Status;
	FRunnableEventQueue EventQueue;

protected:
	virtual bool NativeInit() = 0;
	virtual void NativeExit() = 0;
};
