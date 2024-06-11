#pragma once

class FRHIViewport;

class FDynamicRHI
{
public:
	static FDynamicRHI* Get() { return Singleton; }

protected:
	static FDynamicRHI* Singleton;

public:
	virtual void Init() = 0;
	virtual void Exit() = 0;

public:
	virtual FRHIViewport* CreateRHIViewport() = 0;
};
