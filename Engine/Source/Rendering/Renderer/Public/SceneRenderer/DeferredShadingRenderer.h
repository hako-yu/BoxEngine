#pragma once

#include "SceneRenderer/BaseRenderer.h"

class FRHIPass;

class FDeferredShadingRenderer : public FBaseRenderer
{
public:
    FDeferredShadingRenderer();
    ~FDeferredShadingRenderer();

public:
    virtual void InitPass() override;
    virtual void Render() override;

protected:
    void InitPrePass();
    void InitBasePass();
protected:
    FRHIPass* PrePass = nullptr;
    FRHIPass* BasePass = nullptr;
};
