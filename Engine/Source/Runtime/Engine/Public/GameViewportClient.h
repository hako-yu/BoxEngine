
#pragma once

#include "CoreMinimal.h"

#include "UObject/UObject.h"

class FCanvas;

class UGameViewportClient : public UObject, public IPlatformAppCallbackInterface
{

public:
    void Init();
    void PumpMessages();

    void Draw();

private:
    virtual void OnActivate() override;
    virtual void OnDestory() override;

    virtual void OnResize() override;

    virtual void OnMouseDown() override;
    virtual void OnMouseUp() override;
    virtual void OnMouseMove() override;

private:
    FCanvas* Canvas;
};
