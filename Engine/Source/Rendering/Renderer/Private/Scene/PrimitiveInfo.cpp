#include "Scene/PrimitiveInfo.h"

FPrimitiveInfo::FPrimitiveInfo(const FMeshGeometry& InMesh, const FTransform& InTrans)
	: Mesh(InMesh)
	, Transform(InTrans)
{

}
