
#include "Process/PlatformProcess.h"

#include <windows.h>

void FPlatformProcess::SleepForSeconds(float Seconds)
{
	Sleep(Seconds * 1000.f);
}
