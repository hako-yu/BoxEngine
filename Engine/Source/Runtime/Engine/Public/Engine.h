
#pragma once

#include "CoreMinimal.h"

#include "UObject/UObject.h"

class UGameViewportClient;
class UWorld;

class UEngine : public UObject
{

public:
	static UEngine* CreateEngine();
	
public:
	void Init();
	void Start();
	void Exit();

	void RequestingExit();

protected:
	void PreInitRenderCore();

public:
	UGameViewportClient* GameViewportClient;
	UWorld* World;

private:
	bool bIsRequestingExit = false;
};

extern UEngine* GEngine;
