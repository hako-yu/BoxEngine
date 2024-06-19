#pragma once

#include "CoreMinimal.h"

class FPrimitiveInfo
{
public:
	FPrimitiveInfo(FString FilePath);

protected:
	TArray<FVector> Vertexs;
};
