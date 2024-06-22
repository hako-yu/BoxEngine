#pragma once

#include "CoreMinimal.h"

class FPrimitiveInfo
{
public:
	FPrimitiveInfo();
	FPrimitiveInfo(const FString& FilePath);

protected:
	TArray<FVector> Vertexs;
};
