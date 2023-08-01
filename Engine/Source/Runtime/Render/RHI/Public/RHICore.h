
#pragma once

class FRHICore
{
public:
	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
};

extern FRHICore* GRHICore;
