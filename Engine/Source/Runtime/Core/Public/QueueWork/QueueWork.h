
#pragma once

#include "PlatformMinimal.h"

#include "QueueWork/QueueWorkExecutor.h"

#include <shared_mutex>

template<typename InFuncType>
class FQueueWork
{
	typedef typename FQueueWorkExecutor<InFuncType> ExecutorType;

public:
	void EnqueueEvent(InFuncType& EventFunc)
	{
		Mutex.lock();
		EventList.Push(EventFunc);
		Mutex.unlock();
	}

	void RegisterExecutor(ExecutorType* Executor)
	{
		if (!bIsRunning)
		{
			ExecutorList.Add(Executor);
		}
	}

	void Run()
	{
		bIsRunning = true;

		while (!bRequestExit)
		{
			ExecutorType* Executor = GetExecutor();
			InFuncType* EventFunc = GetTopEventFunc();

			if (Executor != nullptr && EventFunc != nullptr)
			{
				Executor->Exec(*EventFunc);
				OnExecuteComplete();
			}
			else
			{
				FPlatformProcess::SleepForSeconds(0.01);
			}
		}
	}

	void Stop()
	{
		bRequestExit = true;
	}

	bool IsEmpty()
	{
		Mutex.lock_shared();
		bool Res = EventList.empty();
		Mutex.unlock_shared();
		return Res;
	}

private:
	ExecutorType* GetExecutor()
	{
		for (ExecutorType* Executor : ExecutorList)
		{
			if (Executor->CanExec())
			{
				return Executor;
			}
		}

		return nullptr;
	}

	InFuncType* GetTopEventFunc()
	{
		Mutex.lock_shared();
		InFuncType* Func = EventList.Front();
		Mutex.unlock_shared();
		return Func;
	}
	
	void OnExecuteComplete()
	{
		Mutex.lock();
		EventList.Pop();
		Mutex.unlock();
	}

private:
	TQueue<InFuncType> EventList;
	TArray<ExecutorType*> ExecutorList;

	std::shared_mutex Mutex;

	bool bIsRunning = false;
	bool bRequestExit = false;
};
