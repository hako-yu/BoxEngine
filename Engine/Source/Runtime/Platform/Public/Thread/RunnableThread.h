
#include "CoreTypes/CoreTypes.h"

class FRunnable;

class FRunnableThread
{
public:
	static FRunnableThread* Create(FRunnable* InRunnable);

	virtual void Kill() = 0;

protected:
	uint32 ThreadID;

	FRunnable* Runnable;

protected:
	virtual void CreateInternal() = 0;
};
