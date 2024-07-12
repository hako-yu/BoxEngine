#pragma once

#include "CoreMinimal.h"

class FMeshGeometry
{
public:
	FMeshGeometry() {}

public:
	TArray<FVector> Vertexs;
	TArray<int> Indexs;
};
