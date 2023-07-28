
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

FRunnableEvent* FRunnableEventQueue::Pop()
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

	return Lambda;
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
		FRunnableEvent* Event = EventQueue.Pop();
		if (Event)
		{
			(*Event)(this);
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
