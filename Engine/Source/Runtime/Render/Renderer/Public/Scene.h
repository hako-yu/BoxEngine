
#pragma once

#include "CoreMinimal.h"

class FPrimitiveSceneInfo;

class FScene
{
public:
	void RefreshPrimitiveList();

private:
	TArray<FPrimitiveSceneInfo> PrimitiveList;
};
