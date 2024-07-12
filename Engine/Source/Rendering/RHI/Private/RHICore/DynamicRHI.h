#pragma once

class FRHICommands;

class FDynamicRHI
{
public:
	static FDynamicRHI* Get() { return Singleton; }
protected:
	static FDynamicRHI* Singleton;

public:
	static FRHICommands* GetRHICommands() { return Singleton->RHICommands; }
protected:
	FRHICommands* RHICommands;

public:
	virtual void Init() = 0;
	virtual void Exit() = 0;

	virtual void EnableDebug() = 0;
};
