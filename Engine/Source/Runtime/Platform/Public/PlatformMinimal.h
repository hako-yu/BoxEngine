
#pragma once

// BasicTypes
#include "PlatformTypes.h"

// MoreTypes
#include "CoreTypes/Function.h"
#include "CoreTypes/Array.h"
#include "CoreTypes/Queue.h"

#ifdef PLATFORM_WINDOWS
#include "Windows/WindowsPlatformProcess.h"
#include "Windows/WindowsPlatformThread.h"
#include "Windows/WindowsPlatformApp.h"
#endif
