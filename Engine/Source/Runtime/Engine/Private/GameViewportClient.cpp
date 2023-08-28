
#include "GameViewportClient.h"

#include "Engine.h"
#include "RenderingThread.h"
#include "Canvas.h"
#include "SceneRenderer.h"

void UGameViewportClient::Init()
{
	GPlatformAppProc = this;
	FPlatformApplication::CreateMainWindow();
	FPlatformApplication::ShowMainWindow();

	Canvas = new FCanvas(GPlatformAppConfig.WindowHandle, GPlatformAppConfig.Width, GPlatformAppConfig.Height);
}

void UGameViewportClient::PumpMessages()
{
	FPlatformApplication::PumpMessages();
}

void UGameViewportClient::Draw()
{
	FCanvas* TargetCanvas = Canvas;
	FRenderingThread::EnqueueRenderingCommand([TargetCanvas]()
		{
			FSceneRenderer SceneRenderer(nullptr, TargetCanvas);
			SceneRenderer.Render();
		});
	FRenderingThread::FlushRenderingCommands();
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
