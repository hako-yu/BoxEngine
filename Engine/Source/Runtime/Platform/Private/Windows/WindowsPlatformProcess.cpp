
#include "Windows/WindowsPlatformProcess.h"

#include <windows.h>

void FWindowsPlatformProcess::SleepForSeconds(float Seconds)
{
	Sleep(Seconds * 1000.f);
}
