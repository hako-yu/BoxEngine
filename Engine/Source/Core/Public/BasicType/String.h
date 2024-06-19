#pragma once

#include <string>

class FString : protected std::string
{
public:
    FString(const char* str);
}
