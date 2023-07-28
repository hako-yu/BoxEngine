
#pragma once

#include "RHICore.h"

class FD3D12Core : public FRHICore
{
public:
	static FD3D12Core* Create();

protected:


protected:
	virtual void Init() override;
	virtual void Draw() override;

};
