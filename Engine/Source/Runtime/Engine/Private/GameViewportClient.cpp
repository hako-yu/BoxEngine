
#include "GameViewportClient.h"

#include "Engine.h"
#include "RenderingThread.h"

void UGameViewportClient::Init()
{
	GPlatformAppProc = this;
	FPlatformApplication::CreateMainWindow();
	FPlatformApplication::ShowMainWindow();
}

void UGameViewportClient::PumpMessages()
{
	FPlatformApplication::PumpMessages();
}

void UGameViewportClient::Draw()
{
	FRenderingThread::Draw();
}

void UGameViewportClient::OnActivate()
{

}

void UGameViewportClient::OnDestory()
{
	GEngine->RequestingExit();
}

void UGameViewportClient::OnResize()
{

}

void UGameViewportClient::OnMouseDown()
{

}

void UGameViewportClient::OnMouseUp()
{

}

void UGameViewportClient::OnMouseMove()
{

}
