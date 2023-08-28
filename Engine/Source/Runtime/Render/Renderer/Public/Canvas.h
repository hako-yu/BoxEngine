
#pragma once

#include "CoreMinimal.h"

class FRHIViewport;

class FCanvas
{
public:
	FCanvas(void* WindowHandle, uint32 SizeX, uint32 SizeY);
	~FCanvas();

private:
	FRHIViewport* RHIViewport;
};
