
#pragma once

#include "PlatformMinimal.h"

class FRunnable;

class FRunnableThread : FPlatformThread
{
public:
    static FRunnableThread* Create(FRunnable* InRunnable, const WCHAR* ThreadName, uint32 InStackSize = 0);

    FRunnableThread(const WCHAR* ThreadName) : FPlatformThread(ThreadName) {}
    ~FRunnableThread() {}

protected:
    virtual void ThreadEntry() override;

private:
    FRunnable* Runnable;
};
