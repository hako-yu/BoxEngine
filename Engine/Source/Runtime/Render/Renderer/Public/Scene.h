
#pragma once

#include "CoreMinimal.h"

class UWorld;
class FPrimitiveSceneInfo;

class FScene
{
public:
	FScene(UWorld* InWorld);
	~FScene();

public:
	void RefreshPrimitiveList();

private:
	UWorld* World;

	TArray<FPrimitiveSceneInfo> PrimitiveList;
};
