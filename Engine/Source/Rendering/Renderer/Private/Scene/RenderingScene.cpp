#include "Scene/RenderingScene.h"

FPrimitiveInfo* FRenderingScene::AddMesh(const FMeshGeometry& InMesh, const FTransform& InTrans)
{
	PrimitiveInfos.push_back(FPrimitiveInfo(InMesh, InTrans));
}
