#pragma once

#include "CoreMinimal.h"
#include "Scene/CameraInfo.h"
#include "Geometry/MeshGeometry.h"
#include "Math/Transform.h"
#include "Scene/PrimitiveInfo.h"

class FRenderingScene
{
public:
	FPrimitiveInfo* AddMesh(
		const FMeshGeometry& InMesh,
		const FTransform& InTrans
	);

protected:
	FCameraInfo CameraInfo;
	TArray<FPrimitiveInfo> PrimitiveInfos;
};
