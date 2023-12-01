
#pragma once

#include "CoreMinimal.h"

class FRDGBuilder
{
public:
	void AddPass(FString PassName);
	void Compile();
	void Execute();
};
