#pragma once

#include "CoreMinimal.h"
#include "Scene/CameraInfo.h"
#include "Scene/PrimitiveInfo.h"

class FRenderingScene
{
protected:
	FCameraInfo CameraInfo;

	TArray<FPrimitiveInfo> PrimitiveInfos;
};
