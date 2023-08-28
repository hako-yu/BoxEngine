
#pragma once

#include "CoreMinimal.h"

typedef TFunction<void(class FRHI*)> FRHICommandFunc;

class FRHIThread
{
public:
	static void StartRHIThread();
	static void StopRHIThread();

	static void EnqueueRHICommand(FRHICommandFunc Lambda);
	static void FlushRHICommands();
};
