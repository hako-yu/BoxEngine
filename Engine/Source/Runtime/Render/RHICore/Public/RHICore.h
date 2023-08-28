
#pragma once

#include "CoreMinimal.h"

class FRHI;

class FRHICore
{
public:
	static void InitRHICore();

	static FRHI* GetCurrentRHI();
	static void SwitchRHI();

private:
	TArray<FRHI*> RHIList;
	FRHI* CurrentRHI;
};
