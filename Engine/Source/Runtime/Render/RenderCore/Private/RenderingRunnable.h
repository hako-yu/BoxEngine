
#pragma once

#include "Runnable/Runnable.h"
#include "QueueWork/QueueWorkExecutor.h"
#include "RenderingThread.h"

// QueueWork is temporary plan, should be replaced by TaskGraph.
class FRenderingCommandExecutor : public FQueueWorkExecutor<FRenderingCommandFunc>
{
protected:
    virtual void ExecInternal(const FRenderingCommandFunc& InFunc) override
    {
        InFunc();
    }
};

class FRenderingRunnable : public FRunnable
{
public:
    virtual void Init() override;
    virtual void Run() override;
    virtual void Stop() override;
	virtual void Exit() override;

private:
    // QueueWork is temporary plan, should be replaced by TaskGraph.
    FRenderingCommandExecutor* QueueWorkExecutor;
};
