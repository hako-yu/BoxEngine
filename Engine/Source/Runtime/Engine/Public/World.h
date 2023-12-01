
#pragma once

#include "UObject/UObject.h"

class FScene;

class UWorld : public UObject
{
public:
	void Init();

public:
	FScene* GetScene() { return Scene; }

private:
	FScene* Scene;
};
