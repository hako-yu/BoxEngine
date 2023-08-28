
#pragma once

#include "Runnable/Runnable.h"
#include "QueueWork/QueueWorkExecutor.h"
#include "RHIThread.h"

class FRHI;
class FRHICommandList;
class FRHIRunnable;

// QueueWork is temporary plan, should be replaced by TaskGraph.
class FRHICommandExecutor : public FQueueWorkExecutor<FRHICommandFunc>
{
public:
    FRHICommandExecutor(const FRHIRunnable* InRunnable) : Runnable(InRunnable) {}

protected:
    virtual void ExecInternal(const FRHICommandFunc& InFunc) override;

private:
    const FRHIRunnable* Runnable;
};

class FRHIRunnable : public FRunnable
{
public:
    virtual void Init() override;
    virtual void Run() override;
    virtual void Stop() override;
    virtual void Exit() override;

public:
    FRHI* GetCurrentRHI() const;

private:
    FRHI* CurrentRHI;

    // QueueWork is temporary plan, should be replaced by TaskGraph.
    FRHICommandExecutor* QueueWorkExecutor;
};
