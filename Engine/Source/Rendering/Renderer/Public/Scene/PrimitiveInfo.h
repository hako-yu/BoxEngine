#pragma once

#include "CoreMinimal.h"
#include "Geometry/MeshGeometry.h"

class FPrimitiveInfo
{
public:
	FPrimitiveInfo(
		const FMeshGeometry& InMesh,
		const FTransform& InTrans
	);

protected:
	FMeshGeometry Mesh;
	FTransform Transform;
};
