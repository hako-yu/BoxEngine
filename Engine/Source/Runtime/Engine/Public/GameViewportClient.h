
#pragma once

#include "CoreMinimal.h"

#include "UObject.h"

class UGameViewportClient : public UObject
{

public:
    void Init();

public:
    void InputKey();
};
