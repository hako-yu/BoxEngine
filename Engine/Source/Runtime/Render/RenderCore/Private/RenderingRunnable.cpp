
#include "RenderingRunnable.h"

#include "RHICore.h"

void FRenderingRunnable::Draw()
{
	GRHICore->Draw();
}

bool FRenderingRunnable::NativeInit()
{
	return true;
}

void FRenderingRunnable::NativeExit()
{

}
