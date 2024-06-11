#include "Logging.h"

#include <windows.h>
#include <string>
#include <format>

void FMessageLog::AddMessage(const char* File, int Line, const char* Format, ...)
{
	/*
	va_list Args;
	va_start(Args, Line);
	
	va_end(Args);
	*/

	std::string OutStr = std::format("[File: {}, Line: {}]\n{}\n", File, Line, Format);
	OutputDebugString(OutStr.c_str());
}
