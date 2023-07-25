
#include "Engine.h"

#include "Process/PlatformProcess.h"
#include "GameViewportClient.h"

extern UEngine* GEngine = nullptr;

UEngine* UEngine::CreateEngine()
{
	if (GEngine == nullptr)
	{
		GEngine = NewObject<UEngine>();
	}

	return GEngine;
}

void UEngine::Init()
{
	GameViewportClient = NewObject<UGameViewportClient>();
	GameViewportClient->Init();
}

void UEngine::Start()
{
	while (!bIsRequestingExit)
	{
		GameViewportClient->PumpMessages();
		FPlatformProcess::SleepForSeconds(.1f);
	}
}

void UEngine::Exit()
{
	
}

void UEngine::RequestingExit()
{
	bIsRequestingExit = true;
}
