
#pragma once

#include "CoreMinimal.h"

typedef TFunction<void()> FRenderingCommandFunc;

class FRenderingThread
{
public:
	static void StartRenderingThread();
	static void StopRenderingThread();

	static void EnqueueRenderingCommand(FRenderingCommandFunc Lambda);
	static void FlushRenderingCommands();
};
