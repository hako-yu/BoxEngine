
#pragma once

#include "Generic/GenericPlatformTypes.h"

class FWindowsPlatformTypes : public FGenericPlatformTypes
{

public:

    typedef unsigned long   SIZE_T;
    typedef long            SSIZE_T;

    // typedef UTF8CHAR TCHAR;
};

typedef FWindowsPlatformTypes FPlatformTypes;
