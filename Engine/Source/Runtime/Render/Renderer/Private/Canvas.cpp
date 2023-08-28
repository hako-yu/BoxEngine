
#include "Canvas.h"

#include "RHICore.h"
#include "RHI.h"

FCanvas::FCanvas(void* WindowHandle, uint32 SizeX, uint32 SizeY)
{
	FRHI* CurrentRHI = FRHICore::GetCurrentRHI();
	RHIViewport = CurrentRHI->CreateViewport(WindowHandle, SizeX, SizeY);
}

FCanvas::~FCanvas()
{

}
