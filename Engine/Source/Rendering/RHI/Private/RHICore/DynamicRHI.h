#pragma once

class FRHIViewport;
class FRHICommands;

class FDynamicRHI
{
public:
	static FDynamicRHI* Get() { return Singleton; }
	static FRHICommands* GetRHICommands() { return Singleton->RHICommands; }

protected:
	static FDynamicRHI* Singleton;

protected:
	FRHICommands* RHICommands;

public:
	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void EnableDebug() = 0;
};
