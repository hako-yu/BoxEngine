
#pragma once

#include "D3D12ThirdParty.h"

#ifndef ThrowIfFailed
#define ThrowIfFailed(x)               \
{                                      \
    HRESULT hr__ = (x);                \
    if(FAILED(hr__)) { throw hr__; }   \
}
#endif
