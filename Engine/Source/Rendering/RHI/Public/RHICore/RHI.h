#pragma once

class FRHICommands;

class FRHI
{
public:
	static void Init();
	static void Exit();

	static FRHICommands* GetRHICommands();
};
