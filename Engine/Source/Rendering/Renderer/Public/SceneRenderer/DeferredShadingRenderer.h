#pragma once

#include "SceneRenderer/BaseSceneRenderer.h"

class FDeferredShadingRenderer : public FBaseSceneRenderer
{
public:
    virtual void Render() override;
}
