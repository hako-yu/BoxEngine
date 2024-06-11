#pragma once

#define BOX_LOG(Format, ...) FMessageLog::AddMessage(__FILE__, __LINE__, Format, ##__VA_ARGS__)

class FMessageLog
{
public:
	static void AddMessage(const char* File, int Line, const char* Format, ...);
};
