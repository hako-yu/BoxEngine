
#pragma once

#include "CoreMinimal.h"

class FRHIViewport
{
public:
	FRHIViewport(uint32 SizeX, uint32 SizeY);
	~FRHIViewport();

protected:
	uint32 SizeX = 1024;
	uint32 SizeY = 768;
};
