
#pragma once

class FRenderingThread
{
public:
	static void StartRenderingThread();
	static void StopRenderingThread();

	static void Draw();
};
