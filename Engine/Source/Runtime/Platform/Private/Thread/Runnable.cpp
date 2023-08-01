
#include "Thread/Runnable.h"
#include "Process/PlatformProcess.h"

void FRunnableStatus_ThreadSafe::Set(ERunnableStatus InStatus)
{
	Mutex.lock();
	Status = InStatus;
	Mutex.unlock();
}

ERunnableStatus FRunnableStatus_ThreadSafe::Get()
{
	Mutex.lock_shared();
	ERunnableStatus Res = Status;
	Mutex.unlock_shared();

	return Res;
}

void FRunnableEventQueue::Push(FRunnableEvent Lambda)
{
	Mutex.lock();
	Queue.Push(Lambda);
	Mutex.unlock();
}

void FRunnableEventQueue::Pop()
{
	Mutex.lock_shared();
	FRunnableEvent* Lambda = Queue.Front();
	Mutex.unlock_shared();

	if (Lambda)
	{
		Mutex.lock();
		Queue.Pop();
		Mutex.unlock();
	}
}

FRunnableEvent* FRunnableEventQueue::Front()
{
	Mutex.lock_shared();
	FRunnableEvent* Lambda = Queue.Front();
	Mutex.unlock_shared();

	return Lambda;
}

bool FRunnableEventQueue::IsFull()
{
	Mutex.lock_shared();
	uint8 Len = Queue.Num();
	Mutex.unlock_shared();

	return MaxQueueLen <= Len;
}

void FRunnable::Init()
{
	Status.Set(ERunnableStatus::Created);
	if (NativeInit())
	{
		Run();
	}
	else
	{
		// Kill
	}
}

void FRunnable::Run()
{
	Status.Set(ERunnableStatus::Running);
	
	while (Status.Get() == ERunnableStatus::Running)
	{
		FRunnableEvent* Event = EventQueue.Front();
		if (Event)
		{
			(*Event)(this);
			EventQueue.Pop();
		}
		else
		{
			FPlatformProcess::SleepForSeconds(.05f);
		}
	}

	Exit();
}

void FRunnable::Exit()
{
	NativeExit();

	Status.Set(ERunnableStatus::Exitted);
}

void FRunnable::Kill()
{
	Status.Set(ERunnableStatus::Killing);
}
