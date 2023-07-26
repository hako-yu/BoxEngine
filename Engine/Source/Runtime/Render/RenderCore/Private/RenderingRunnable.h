
#include "Thread/Runnable.h"

class FRenderingRunnable : public FRunnable
{
protected:
    virtual void Init() override;
    virtual void Run() override;
    virtual void Stop() override;
};
