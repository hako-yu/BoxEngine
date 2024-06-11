#pragma once

#include "RHICore/DynamicRHI.h"

class FD3D12Device;

class FD3D12RHI : public FDynamicRHI
{
public:
	static bool Create();

protected:
	virtual void Init() override;
	virtual void Exit() override;

protected:
	virtual FRHIViewport* CreateRHIViewport() override;

private:
	FD3D12Device* Device;
};
