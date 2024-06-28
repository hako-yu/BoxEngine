#pragma once

#include "RHICore/DynamicRHI.h"

class FD3D12Adapter;

class FD3D12RHI : public FDynamicRHI
{
public:
	static FD3D12RHI* Get() { return static_cast<FD3D12RHI*>(Singleton); }
	static bool Create();

protected:
	virtual void Init() override;
	virtual void Exit() override;

	virtual void EnableDebug() override;

public:
	void InitRootAdapter();

	FD3D12Adapter* GetRootAdapter() { return RootAdapter; }

protected:
	FD3D12Adapter* RootAdapter = nullptr;
};
