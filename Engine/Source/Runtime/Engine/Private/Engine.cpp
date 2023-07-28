
#include "Engine.h"

#include "Process/PlatformProcess.h"
#include "GameViewportClient.h"
#include "RHIThread.h"
#include "RenderingThread.h"

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
	GameViewportClient = NewObject<UGameViewportClient>();
	GameViewportClient->Init();

	FRHIThread::StartRHIThread();
	FRenderingThread::StartRenderingThread();
}

void UEngine::Start()
{
	while (!bIsRequestingExit)
	{
		GameViewportClient->PumpMessages();
		FPlatformProcess::SleepForSeconds(.1f);

		FRenderingThread::Draw();
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
