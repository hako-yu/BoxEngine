
#include "RHIRunnable.h"

#include "RHICore.h"

// QueueWork is temporary plan, should be replaced by TaskGraph.
#include "QueueWork/QueueWork.h"

// QueueWork is temporary plan, should be replaced by TaskGraph.
extern FQueueWork<FRHICommandFunc>* GRHICommandQueueWork;
extern FRHICore* GRHICore;

void FRHICommandExecutor::ExecInternal(const FRHICommandFunc& InFunc)
{
	InFunc(Runnable->GetCurrentRHI());
}

void FRHIRunnable::Init()
{
	CurrentRHI = GRHICore->GetCurrentRHI();

	// QueueWork is temporary plan, should be replaced by TaskGraph.
	QueueWorkExecutor = new FRHICommandExecutor(this);
	GRHICommandQueueWork->RegisterExecutor(QueueWorkExecutor);
}

void FRHIRunnable::Run()
{
	// QueueWork is temporary plan, should be replaced by TaskGraph.
	GRHICommandQueueWork->Run();

}

void FRHIRunnable::Stop()
{
	// QueueWork is temporary plan, should be replaced by TaskGraph.
	GRHICommandQueueWork->Stop();
}

void FRHIRunnable::Exit()
{

}

FRHI* FRHIRunnable::GetCurrentRHI() const
{
	return CurrentRHI;
}
