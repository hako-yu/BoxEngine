#pragma once

#include "CoreMinimal.h"
#include "RHICore/RHICommon.h"

struct FVertexLayout
{
	FString Name;
	ERHIVertexLayoutItemFormat Format;
};

class FVertexFactor
{
public:
	FVertexFactor();
	~FVertexFactor();

public:
	void Init();
	void SetupVertexLayout();

protected:
	TArray<FVertexLayout> Layout;
};
