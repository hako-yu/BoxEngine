
#include "RenderingRunnable.h"
#include "RenderingThread.h"

// QueueWork is temporary plan, should be replaced by TaskGraph.
#include "QueueWork/QueueWork.h"

// QueueWork is temporary plan, should be replaced by TaskGraph.
extern FQueueWork<FRenderingCommandFunc>* GRenderingCommandQueueWork;

void FRenderingRunnable::Init()
{
	// QueueWork is temporary plan, should be replaced by TaskGraph.
	QueueWorkExecutor = new FRenderingCommandExecutor();
	GRenderingCommandQueueWork->RegisterExecutor(QueueWorkExecutor);

}

void FRenderingRunnable::Run()
{
	// QueueWork is temporary plan, should be replaced by TaskGraph.
	GRenderingCommandQueueWork->Run();

}

void FRenderingRunnable::Stop()
{
	// QueueWork is temporary plan, should be replaced by TaskGraph.
	GRenderingCommandQueueWork->Stop();
}

void FRenderingRunnable::Exit()
{

}
