#include "TestScene/TestScene.h"

#include "Geometry/Box.h"

void FTestSceneBuildingFunction::BuildTestScene(FRenderingScene* Scene)
{
    Scene->AddMesh(FBox::Create(), FTransform());
}
