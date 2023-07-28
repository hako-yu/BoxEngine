
#pragma once

#include "CoreTypes/BasicTypes.h"

#include <string>

class FString : public std::wstring
{

public:
	FString() : std::wstring() {}
	// FString(const ANSICHAR* Str) : std::wstring(Str) {}
	FString(const WIDECHAR* Str) : std::wstring(Str) {}
	// FString(const UTF8CHAR* Str) : std::wstring(Str) {}
	// FString(const UCS2CHAR* Str) : std::wstring(Str) {}

};
