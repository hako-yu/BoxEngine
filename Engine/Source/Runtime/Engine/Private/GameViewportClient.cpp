
#include "GameViewportClient.h"

#include "Engine.h"

void UGameViewportClient::Init()
{
	PlatformAppProc = this;
	FPlatformApplication::CreateMainWindow();
	FPlatformApplication::ShowMainWindow();
}

void UGameViewportClient::PumpMessages()
{
	FPlatformApplication::PumpMessages();
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
