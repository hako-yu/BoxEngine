
#include "Engine.h"

#include "CoreMinimal.h"

#include "RHICore.h"
#include "RHIThread.h"
#include "RenderingThread.h"

#include "GameViewportClient.h"

UEngine* GEngine = nullptr;

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
	// Init Render Core
	PreInitRenderCore();

	// Init Viewport
	GameViewportClient = NewObject<UGameViewportClient>();
	GameViewportClient->Init();

	// Init World
}

void UEngine::Start()
{
	while (!bIsRequestingExit)
	{
		if (GameViewportClient)
		{
			GameViewportClient->PumpMessages();
			GameViewportClient->Draw();
		}
		else
		{
			FPlatformProcess::SleepForSeconds(.1f);
		}
	}
}

void UEngine::Exit()
{
	FRenderingThread::StopRenderingThread();
	FRHIThread::StopRHIThread();
}

void UEngine::RequestingExit()
{
	bIsRequestingExit = true;
}

void UEngine::PreInitRenderCore()
{
	// Init RHI
	FRHICore::InitRHICore();
	FRHIThread::StartRHIThread();

	// Init Render
	FRenderingThread::StartRenderingThread();
}
