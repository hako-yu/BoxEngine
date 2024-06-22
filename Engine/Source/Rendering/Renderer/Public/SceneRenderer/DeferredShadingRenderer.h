#pragma once

#include "SceneRenderer/BaseSceneRenderer.h"

class FDeferredShadingRenderer : public FBaseSceneRenderer
{
public:
    FDeferredShadingRenderer(FRenderingScene* InScene, FViewport* InViewport);
    ~FDeferredShadingRenderer();

public:
    virtual void Render() override;
};
