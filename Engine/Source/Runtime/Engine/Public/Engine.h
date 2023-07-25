
#pragma once

#include "CoreMinimal.h"

#include "UObject/UObject.h"

class UGameViewportClient;

class UEngine : public UObject
{

public:
	static UEngine* CreateEngine();
	
public:
	void Init();
	void Start();
	void Exit();

	void RequestingExit();

public:
	UGameViewportClient* GameViewportClient;

private:
	bool bIsRequestingExit = false;
};

extern UEngine* GEngine;
