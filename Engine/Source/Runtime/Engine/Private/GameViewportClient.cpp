
#include "GameViewportClient.h"

#include "Engine.h"
#include "RenderingThread.h"
#include "World.h"
#include "Scene.h"
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

void UGameViewportClient::Draw(UWorld* InWorld)
{
	FScene* Scene = InWorld->GetScene();
	FCanvas* TargetCanvas = Canvas;

	Scene->RefreshPrimitiveList();
	FRenderingThread::EnqueueRenderingCommand([Scene, TargetCanvas]()
		{
			FSceneRenderer SceneRenderer(Scene, TargetCanvas);
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
