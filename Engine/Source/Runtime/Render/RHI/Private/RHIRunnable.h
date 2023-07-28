
#pragma once

#include "Thread/Runnable.h"

class FRHICore;

class FRHIRunnable : public FRunnable
{
protected:
    FRHICore* RHICore;

protected:
    virtual bool NativeInit() override;
    virtual void NativeExit() override;
};
