#pragma once

#include "RHICore/DynamicRHI.h"

class FD3D12Adapter;

class FD3D12RHI : public FDynamicRHI
{
public:
	static bool Create();

protected:
	virtual void Init() override;
	virtual void Exit() override;

protected:
	virtual FRHIViewport* CreateRHIViewport() override;

protected:
	void InitRootAdapter();

private:
	FD3D12Adapter* RootAdapter = nullptr;
};
